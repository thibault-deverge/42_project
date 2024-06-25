// SPDX-License-Identifier: MIT
pragma solidity  ^0.8.0;

contract tournament {

    struct Game{
        uint player1;
        uint player2;
        uint16 score1;
        uint16 score2;
		uint16 ballHits;
    }

    struct Tournament{
        Game[3] gameArr;
    }

	Tournament curr;

    function setGame
    (uint16 gameNumber, uint Player1, uint Player2)
    public
    {
        curr.gameArr[gameNumber].player1 = Player1;
        curr.gameArr[gameNumber].player2 = Player2;
    }

    function setScore
    (uint16 gameNumber, uint16 score1, uint16 score2)
    public
    {
		curr.gameArr[gameNumber].score1 = score1;
		curr.gameArr[gameNumber].score2 = score2;
    }

    function setAll(
    uint[6] memory Players, uint16[6] memory Score, uint16[3] memory BallHitsArr)
    public
    {
        curr.gameArr[0].player1 = Players[0];
        curr.gameArr[0].score1 = Score[0];
        curr.gameArr[0].player2 = Players[1];
        curr.gameArr[0].score2 = Score[1];
		curr.gameArr[0].ballHits = BallHitsArr[0];

        curr.gameArr[1].player1 = Players[2];
        curr.gameArr[1].score1 = Score[2];
        curr.gameArr[1].player2 = Players[3];
        curr.gameArr[1].score2 = Score[3];
		curr.gameArr[1].ballHits = BallHitsArr[1];

        curr.gameArr[2].player1 = Players[4];
        curr.gameArr[2].score1 = Score[4];
        curr.gameArr[2].player2 = Players[5];
        curr.gameArr[2].score2 = Score[5];
		curr.gameArr[2].ballHits = BallHitsArr[2];
    }

    function getData()
    public
    view
    returns (uint[6] memory, uint16[6] memory, uint16[3] memory)
    {
        uint[6] memory Players;
        uint16[6] memory Score;
        uint16[3] memory BallHits;
        uint j = 0;
        for (uint i = 0; i < 3; i++){
            Players[j] = curr.gameArr[i].player1;
            Players[j+1] = curr.gameArr[i].player2;
            Score[j] = curr.gameArr[i].score1;
            Score[j+1] = curr.gameArr[i].score2;
			BallHits[i] = curr.gameArr[i].ballHits;
            j+=2;
        }
        return (Players, Score, BallHits);
    }
}


