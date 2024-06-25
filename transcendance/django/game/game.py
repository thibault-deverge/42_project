from channels.layers import get_channel_layer
import asyncio
import json
import random

all_room = {}
all_private_room = {}
PLAYER_SPEED = 0.015
BALL_MAX_SPEED = 0.015
BALL_RADIUS_RATIO = 0.01
PLAYER_HEIGHT_RATIO = 0.13
PLAYER_WIDTH_RATIO = 0.015
POINT_TO_WIN = 3

async def timer(time, channel_name, channel_layer, room_group_name):
    for i in range(time):
        msg = create_msg(channel_name, "TIMER")
        msg = add_info(msg, "SEC", time - i)
        await channel_layer.group_send(room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        await asyncio.sleep(1)

def create_msg_game(player_2, event, game):
    data = {
        'player_2': player_2,
        'data': {
            'event': event,
            'game': game
        }
    }
    return data

def create_msg(sender ,msg):
    data = {
            'sender': sender,
            'event': msg,
        }
    data = json.dumps(data)
    return data

def add_info(data, key, value):
    updated = json.loads(data)
    updated[key] = value
    updated = json.dumps(updated)
    return updated

async def reset(game):
    game["ball"]["x"] = 0.5
    game["ball"]["y"] = 0.5
    game["player1"]["y"] = 0.5 - PLAYER_HEIGHT_RATIO / 2
    game["player2"]["y"] = 0.5 - PLAYER_HEIGHT_RATIO / 2

    if random.random() >= 0.5:
        game["ball"]["speed"]["x"] = -0.004
    else:
        game["ball"]["speed"]["x"] = 0.004
    game["ball"]["speed"]["y"] = (3 - random.random() * 6) / 1000

async def change_direction(game, player_position, y):
    impact = y - player_position - PLAYER_HEIGHT_RATIO / 2
    ratio = 80 / (PLAYER_HEIGHT_RATIO / 2)
    game["ball"]["speed"]["y"] = round(impact * ratio / 10) / 1000

async def collide(game, x, y):
    if (x - game["ball"]["r"]) <= 0.01 + PLAYER_WIDTH_RATIO and (x - game["ball"]["r"]) >= 0.01:
        if(((y + game["ball"]["r"]) <= (game["player1"]["y"]) + PLAYER_HEIGHT_RATIO and (y + game["ball"]["r"]) >= (game["player1"]["y"]) )
                or (y - game["ball"]["r"]) <= (game["player1"]["y"]) + PLAYER_HEIGHT_RATIO and (y - game["ball"]["r"]) >= (game["player1"]["y"])):
            if game["ball"]["speed"]["x"] < 0:
                game["ball"]["speed"]["x"] *= -1
                await change_direction(game, game["player1"]["y"], y)
            if abs(game["ball"]["speed"]["x"]) * 1.1 > BALL_MAX_SPEED:
                game["ball"]["speed"]["x"] = BALL_MAX_SPEED
            else:
                game["ball"]["speed"]["x"] *= 1.1
            game["statistic"]["ball_hit"] += 1
            return 1
    elif (x + game["ball"]["r"]) >= 1 - (PLAYER_WIDTH_RATIO + 0.01) and (x + game["ball"]["r"]) <= 1 - 0.01:
        if (((y + game["ball"]["r"]) <= (game["player2"]["y"]) + PLAYER_HEIGHT_RATIO and (y + game["ball"]["r"]) >= (game["player2"]["y"]))
                or (y - game["ball"]["r"]) <= (game["player2"]["y"]) + PLAYER_HEIGHT_RATIO and (y - game["ball"]["r"]) >= (game["player2"]["y"])):
            if game["ball"]["speed"]["x"] > 0:
                game["ball"]["speed"]["x"] *= -1
                await change_direction(game, game["player2"]["y"], y)
            if abs(game["ball"]["speed"]["x"]) * 1.1 > BALL_MAX_SPEED:
                game["ball"]["speed"]["x"] = -BALL_MAX_SPEED
            else:
                game["ball"]["speed"]["x"] *= 1.1
            game["statistic"]["ball_hit"] += 1
            return 1
    return 0

async def check_collide(game, begin_x, begin_y, end_x, end_y):
    collided = 0
    steps = abs(end_x - begin_x)
    if steps < abs(end_y - begin_y):
        steps = abs(end_y - begin_y)
    dx = abs(end_x - begin_x) / steps
    dy = abs(end_y - begin_y) / steps
    i = 0
    x = begin_x
    y = begin_y
    while i < steps and collided == 0:
        collided = await collide(game, x, y)
        x += dx
        y += dy
        i += 1

async def score(game, channel_layer, room_group_name, player_2):
    msg = create_msg_game(player_2, "SCORE", game)
    await channel_layer.group_send(room_group_name, {
        'type': 'send_game_all',
        "message": msg,
    })
    await timer(2, "game", channel_layer, room_group_name)

async def move(game, channel_layer, room_group_name, player_2, player_1):
    if game["ball"]["y"] + game["ball"]["r"] >= 1 and game["ball"]["speed"]["y"] > 0:
        game["ball"]["speed"]["y"] *= -1
    elif game["ball"]["y"] - game["ball"]["r"] <= 0 and game["ball"]["speed"]["y"] < 0:
        game["ball"]["speed"]["y"] *= -1

    await check_collide(game, game["ball"]["x"], game["ball"]["y"], game["ball"]["x"] + game["ball"]["speed"]["x"], game["ball"]["y"] + game["ball"]["speed"]["y"])
    if game["ball"]["x"] >= 1:
        game["player1"]["score"] += 1
        game["statistic"]["score_order"].append(player_1)
        await score(game, channel_layer, room_group_name, player_2)
        await reset(game)
    elif game["ball"]["x"] <= 0:
        game["player2"]["score"] += 1
        game["statistic"]["score_order"].append(player_2)
        await score(game, channel_layer, room_group_name, player_2)
        await reset(game)

    game["ball"]["x"] += game["ball"]["speed"]["x"]
    game["ball"]["y"] += game["ball"]["speed"]["y"]

async def player_move(game, id, player_1, player_2):
    if all_room[id][player_1]["up"] and not all_room[id][player_1]["down"]:
        game["player1"]["y"] -= PLAYER_SPEED
        if game["player1"]["y"] < 0:
            game["player1"]["y"] = 0
    if all_room[id][player_1]["down"] and not all_room[id][player_1]["up"]:
        game["player1"]["y"] += PLAYER_SPEED
        if game["player1"]["y"] > 1 - PLAYER_HEIGHT_RATIO:
            game["player1"]["y"] = 1 - PLAYER_HEIGHT_RATIO
    if all_room[id][player_2]["up"] and not all_room[id][player_2]["down"]:
        game["player2"]["y"] -= PLAYER_SPEED
        if game["player2"]["y"] < 0:
            game["player2"]["y"] = 0
    if all_room[id][player_2]["down"] and not all_room[id][player_2]["up"]:
        game["player2"]["y"] += PLAYER_SPEED
        if game["player2"]["y"] > 1 - PLAYER_HEIGHT_RATIO:
            game["player2"]["y"] = 1 - PLAYER_HEIGHT_RATIO

async def game(id, player_1, player_2, player1_username, player2_username):
    channel_layer = get_channel_layer()
    room_group_name = 'room_%s' % id
    game = {
        "ball": {
            "x": 0.5,
            "y": 0.5,
            "r": 0.01,
            "speed": {
                "x": 0.5,
                "y": 0.5,
            }
        },
        "player1": {
            "name": player1_username,
            "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
            "score": 0,
            "player": "1"
        },
        "player2": {
            "name": player2_username,
            "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
            "score": 0,
            "player": "2"
        },
        "statistic": {
            "score_order": [],
            "ball_hit": 0,
        }
    }
    await reset(game)
    msg = create_msg_game(player_2, "START", game)
    await channel_layer.group_send(room_group_name, {
        'type': 'send_game_all',
        "message": msg,
    })
    await timer(5, "name", channel_layer, room_group_name)
    while game["player1"]["score"] != POINT_TO_WIN and game["player2"]["score"] != POINT_TO_WIN:
        await player_move(game, id, player_1, player_2)
        await move(game, channel_layer, room_group_name, player_2, player_1)
        msg = create_msg_game(player_2, "GAME", game)
        await channel_layer.group_send(room_group_name, {
            'type': 'send_game_all',
            "message": msg,
        })
        await asyncio.sleep(1 / 60)
    msg = create_msg("game", "END")
    await channel_layer.group_send(room_group_name, {
        'type': 'send_message_all',
        "message": msg,
    })
    return game


         ###### PRIVATE  GAME ########
async def private_player_move(game, id, player_1, player_2):
    if all_private_room[id][player_1]["up"] and not all_private_room[id][player_1]["down"]:
        game["player1"]["y"] -= PLAYER_SPEED
        if game["player1"]["y"] < 0:
            game["player1"]["y"] = 0
    if all_private_room[id][player_1]["down"] and not all_private_room[id][player_1]["up"]:
        game["player1"]["y"] += PLAYER_SPEED
        if game["player1"]["y"] > 1 - PLAYER_HEIGHT_RATIO:
            game["player1"]["y"] = 1 - PLAYER_HEIGHT_RATIO

    if all_private_room[id][player_2]["up"] and not all_private_room[id][player_2]["down"]:
        game["player2"]["y"] -= PLAYER_SPEED
        if game["player2"]["y"] < 0:
            game["player2"]["y"] = 0
    if all_private_room[id][player_2]["down"] and not all_private_room[id][player_2]["up"]:
        game["player2"]["y"] += PLAYER_SPEED
        if game["player2"]["y"] > 1 - PLAYER_HEIGHT_RATIO:
            game["player2"]["y"] = 1 - PLAYER_HEIGHT_RATIO

async def private_game(id, player_1, player_2, player1_username, player2_username):
    channel_layer = get_channel_layer()
    room_group_name = 'room_%s' % id
    game = {
        "ball": {
            "x": 0.5,
            "y": 0.5,
            "r": 0.01,
            "speed": {
                "x": 0.5,
                "y": 0.5,
            }
        },
        "player1": {
            "name": player1_username,
            "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
            "score": 0,
            "player": "1"
        },
        "player2": {
            "name": player2_username,
            "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
            "score": 0,
            "player": "2"
        },
        "statistic": {
            "score_order": [],
            "ball_hit": 0,
        }
    }
    await reset(game)
    msg = create_msg_game(player_2, "START", game)
    await channel_layer.group_send(room_group_name, {
        'type': 'send_game_all',
        "message": msg,
    })
    await timer(5, "name", channel_layer, room_group_name)
    while game["player1"]["score"] != POINT_TO_WIN and game["player2"]["score"] != POINT_TO_WIN:
        # await playerMove(game, id, player_1.id, player_2.id)
        await private_player_move(game, id, player_1, player_2)
        await move(game, channel_layer, room_group_name, player_2, player_1)
        msg = create_msg_game(player_2, "GAME", game)
        await channel_layer.group_send(room_group_name, {
            'type': 'send_game_all',
            "message": msg,
        })
        await asyncio.sleep(1 / 60)
    msg = create_msg("game", "END")
    await channel_layer.group_send(room_group_name, {
        'type': 'send_message_all',
        "message": msg,
    })
    if id in all_private_room:
        del all_private_room[id]