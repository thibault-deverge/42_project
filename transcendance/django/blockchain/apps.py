from django.apps import AppConfig
from web3 import Web3, HTTPProvider
import json

class BlockchainConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'blockchain'

with open('/django/blockchain/contract/Tournament/tournament.abi', "r") as file:
	tournament_abi = json.load(file)
with open('/django/blockchain/contract/Tournament/tournament.bin', 'r') as file:
	tournament_bytecode = file.read()
with open('/django/blockchain/contract/Registry/tournament_registry.abi', "r") as file:
	registry_abi = json.load(file)
with open('/django/blockchain/contract/Registry/tournament_registry.bin', 'r') as file:
	registry_bytecode = file.read()
with open('/django/blockchain/contract/Address.txt', 'r') as file:
    address = file.read()

w3 = Web3(HTTPProvider("http://blockchain:8545"))
w3.eth.default_account = w3.eth.accounts[0]
with open('/django/blockchain/db/account', 'r') as file:
    account = json.load(file)
PK = next(iter(account['private_keys'].values()))

registry_contract = None

try:
    code = w3.eth.get_code(address)
    if code != b'':
        registry_contract = w3.eth.contract(address=address, abi=registry_abi)
    else:
        raise ValueError("NO CONTRACT")
except:
    contract_init = w3.eth.contract(abi=registry_abi, bytecode=registry_bytecode)
    tx_hash = contract_init.constructor().transact()
    tx_receipt = w3.eth.wait_for_transaction_receipt(tx_hash)
    address = tx_receipt.contractAddress
    with open('/django/blockchain/contract/Address.txt', 'w') as file:
        file.write(address)
    registry_contract = w3.eth.contract(address=address, abi=registry_abi)

def createNewTournament():
    addr = deployNewTournament()
    tx_hash = registry_contract.functions.storeNewAddress(addr).build_transaction({
        "nonce" : w3.eth.get_transaction_count(w3.eth.accounts[0]),
    })
    tx_create = w3.eth.account.sign_transaction(tx_hash, PK)
    tx_hash = w3.eth.send_raw_transaction(tx_create.rawTransaction)
    w3.eth.wait_for_transaction_receipt(tx_hash)
    new_contract = w3.eth.contract(address=addr, abi=tournament_abi)
    return new_contract

def setPlayer(Contract, GameNumber, Player1Id, Player2Id):
    tx_hash = Contract.functions.setGame(GameNumber, Player1Id, Player2Id).build_transaction({
        "nonce" : w3.eth.get_transaction_count(w3.eth.accounts[0]),
    })
    tx_create = w3.eth.account.sign_transaction(tx_hash, PK)
    tx_hash = w3.eth.send_raw_transaction(tx_create.rawTransaction)
    w3.eth.wait_for_transaction_receipt(tx_hash)

def setScore(Contract, GameNumber, Score1, Score2):
    tx_hash = Contract.functions.setScore(GameNumber, Score1, Score2).build_transaction({
        "nonce" : w3.eth.get_transaction_count(w3.eth.accounts[0]),
    })
    tx_create = w3.eth.account.sign_transaction(tx_hash, PK)
    tx_hash = w3.eth.send_raw_transaction(tx_create.rawTransaction)
    w3.eth.wait_for_transaction_receipt(tx_hash)

def setAll(Contract, Data):
    playerArr = []
    scoreArr = []
    ballHitArr=[]

    playerArr.append(Data["first_demi"]["player1"]["id"])
    playerArr.append(Data["first_demi"]["player2"]["id"])
    playerArr.append(Data["second_demi"]["player1"]["id"])
    playerArr.append(Data["second_demi"]["player2"]["id"])
    playerArr.append(Data["final"]["player1"]["id"])
    playerArr.append(Data["final"]["player2"]["id"])

    scoreArr.append(Data["first_demi"]["player1"]["score"])
    scoreArr.append(Data["first_demi"]["player2"]["score"])
    scoreArr.append(Data["second_demi"]["player1"]["score"])
    scoreArr.append(Data["second_demi"]["player2"]["score"])
    scoreArr.append(Data["final"]["player1"]["score"])
    scoreArr.append(Data["final"]["player2"]["score"])

    ballHitArr.append(Data["first_demi"]["ball_hit"])
    ballHitArr.append(Data["second_demi"]["ball_hit"])
    ballHitArr.append(Data["final"]["ball_hit"])

    tx_hash = Contract.functions.setAll(playerArr, scoreArr, ballHitArr).build_transaction({
        "nonce" : w3.eth.get_transaction_count(w3.eth.accounts[0]),
    })
    tx_create = w3.eth.account.sign_transaction(tx_hash, PK)
    tx_hash = w3.eth.send_raw_transaction(tx_create.rawTransaction)
    w3.eth.wait_for_transaction_receipt(tx_hash)

def getTournament(id):
    addr = registry_contract.functions.getTournamentAddress(id).call()
    new_contract = w3.eth.contract(address=addr, abi=tournament_abi)
    return new_contract

def getStats(playerId):
    statsArr = [0,0,0,0,0,0,0,0]
    isRegistered = False
    addressArr = registry_contract.functions.getAllAddresses().call()
    if len(addressArr) == 0:
        return None
    for i in range(len(addressArr)):
        tournament = w3.eth.contract(address=addressArr[i], abi=tournament_abi)
        data = tournament.functions.getData().call()
        playerArr = data[0]
        scoreArr = data[1]
        foundInGame = False
        for j in range(len(playerArr)):
            if playerArr[j] == playerId:
                isRegistered = True
                if not foundInGame:
                    statsArr[0] +=1
                statsArr[7] += data[2][j//2]
                if j % 2 == 1:
                    if scoreArr[j-1] < scoreArr[j]: # si notre player gagne
                        statsArr[3] += 1
                        if j == 5:
                            statsArr[1] += 1
                    elif scoreArr[j-1] > scoreArr[j] and j == 5: # si notre player loose et que last game
                        statsArr[6] += 1
                    elif scoreArr[j-1] > scoreArr[j] and j < 5: # si notre player loose (donc pas last game)
                        statsArr[5] += 1
                else:
                    if scoreArr[j] > scoreArr[j+1]: # si notre player gagne
                        statsArr[3] += 1
                        if j == 4:
                            statsArr[1] += 1
                    elif scoreArr[j] < scoreArr[j+1] and j == 4: # si notre player loose et que last game
                        statsArr[6] += 1
                    elif scoreArr[j] < scoreArr[j+1] and j < 4: # si notre player loose (donc pas last game)
                        statsArr[5] += 1
                foundInGame = True
                statsArr[2] += 1
                statsArr[4] += scoreArr[j]
    if isRegistered == False:
        return None
    return statsArr

def deployNewTournament():
    contract_init = w3.eth.contract(abi=tournament_abi, bytecode=tournament_bytecode)
    tx_hash = contract_init.constructor().transact()
    tx_receipt = w3.eth.wait_for_transaction_receipt(tx_hash)
    address = tx_receipt.contractAddress
    return address
