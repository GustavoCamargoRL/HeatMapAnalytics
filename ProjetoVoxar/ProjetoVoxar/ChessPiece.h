#pragma once

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


class ChessPiece {
public:
	int id, B, G, R;  //identificador, valor de azul, verde e vermelho (a fim de identificar os times)
	String name;	  // nome da peça de xadrez para visualização do usuario
	Point2f center;	  //Coordenadas do centro do marcador
	vector<Point2f> pieceMovesPoints;	//Salva os movimentos das peças

	ChessPiece(int id);
	void centerCoord(Point2f p1, Point2f p2);  //cálculo da coordenada central atual da peça
	bool saveMoves();						   //Salva a movimentação da peça e retorna true quando há movimentação
	void heatMap(Mat& frame);				   //Desenha o heat map da peça
	
};
