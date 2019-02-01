#pragma once

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


class ChessPiece {
public:
	int id, B, G, R;  //identificador, valor de azul, verde e vermelho (a fim de identificar os times)
	String name;	  // nome da pe�a de xadrez para visualiza��o do usuario
	Point2f center;	  //Coordenadas do centro do marcador
	vector<Point2f> pieceMovesPoints;	//Salva os movimentos das pe�as

	ChessPiece(int id);
	void centerCoord(Point2f p1, Point2f p2);  //c�lculo da coordenada central atual da pe�a
	bool saveMoves();						   //Salva a movimenta��o da pe�a e retorna true quando h� movimenta��o
	void heatMap(Mat& frame);				   //Desenha o heat map da pe�a
	
};
