#pragma once

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/aruco.hpp"
#include "VideoSave.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;
using namespace cv;


class ArucoMarkers {
public:
	Ptr<aruco::Dictionary> markerDictionary;	//Salva o dicionario utilizado para os marcadores
	vector<vector<Point2f>> corners;			//Guarda a posição de cada quina dos marcadores
	vector<int> ids;							//Guarda o id dos marcadores identificados
	bool move;									//flag para movimentação registrada
	int whiteMoves;								//registra o numero de jogadas do time Branco
	int blackMoves;								//registra o numero de jogadas do time Preto
	bool turn;									//flag de mudança de turno
		
	ArucoMarkers();
	void createArucoMarkers();			// Cria os marcadores e salva na extenção .jpg
	bool detectAruco(Mat& currentFrame, vector<ChessPiece>& allChessPieces, bool gameStart); //Detecta os marcadores, desenhando um circulo preenchido centralizado
																							//junto com o nome da peça de acordo com seu id
																							//quando o jogo começar, passa a salvar as movimentações das peças
};																			
