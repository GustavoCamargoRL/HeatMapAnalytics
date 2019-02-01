#include "ChessPiece.h"

ChessPiece::ChessPiece(int pieceId) {
	id = pieceId;
	center.x = 0.0;
	center.y = 0.0;

	if (id >= 0 && id <= 15) {
		// pe�as brancas
		B = 255;
		G = 255;
		R = 255;
		// nomeclatura de cada pe�a
		if (id == 0 || id == 1) {
			name = "Rook";
		}
		else if (id == 2 || id == 3) {
			name = "Knight";
		}
		else if (id == 4 || id == 5) {
			name = "Bishop";
		}
		else if (id == 6) {
			name = "Queen";
		}
		else if (id == 7) {
			name = "King";
		}
		else {
			name = "Pawn";
		}
	}
	else {
		//pe�as pretas
		B = 0;
		G = 0;
		R = 0;
		// nomeclatura de cada pe�a
		if (id == 16 || id == 17) {
			name = "Rook";
		}
		else if (id == 18 || id == 19) {
			name = "Knight";
		}
		else if (id == 20 || id == 21) {
			name = "Bishop";
		}
		else if (id == 22) {
			name = "Queen";
		}
		else if (id == 23) {
			name = "King";
		}
		else {
			name = "Pawn";
		}
	}
}

void ChessPiece::centerCoord(Point2f p1, Point2f p2) { // metodo para calcular as coordenadas centrais dos marcadores
	if (p1.x < p2.x) {								   // p1 = borda superior esquerda , p2= borda inferior direita, formando uma diagonal,
		center.x = p1.x + ((abs(p2.x - p1.x)) / 2);	   // que independente da rota��o da pe�a ir� identificar o centro corretamente
	}
	else {
		center.x = p2.x + ((abs(p2.x - p1.x)) / 2);
	}
	if (p1.y < p2.y) {
		center.y = p1.y + ((abs(p2.y - p1.y)) / 2);
	}
	else {
		center.y = p2.y + ((abs(p2.y - p1.y)) / 2);
	}
}

bool ChessPiece::saveMoves() { // metodo para salvar a posi��o central da pe�a de xadrez ao se realizar um movimento
	size_t vectorSize = pieceMovesPoints.size();  

	if (vectorSize == 0) {
		pieceMovesPoints.push_back(center);
		return false;
	}
	else {
		//checa se a pe�a se deslocou uma dist�ncia m�nima
		if (abs(pieceMovesPoints[vectorSize - 1].x - center.x) > 40 || abs(pieceMovesPoints[vectorSize - 1].y - center.y) > 40) { //na distancia definida da camera nos testes, 40 pixels +/- a dist�ncia necess�ria para andar 1 casa
			pieceMovesPoints.push_back(center); //salva o ponto atual no vetor
			return true;  //retorna true para indicar que houve movimenta��o de uma pe�a
			
		}
		return false;
	}
}
void ChessPiece::heatMap(Mat& frameInicial) {
	size_t vectorSize = pieceMovesPoints.size();
	String team;
	ostringstream convert;

	if (vectorSize > 0) {  //checa se houve movimenta��o da pe�a
		for (int i = 1; i < vectorSize; i++) {
			line(frameInicial, pieceMovesPoints[i - 1], pieceMovesPoints[i], Scalar(0, 255, 0), 3, LINE_AA, 0); //desenha uma linha do ponto i-1 ate o ponto i

			if (i == 1) {
				circle(frameInicial, pieceMovesPoints[i - 1], 5, Scalar(0, 0, 255), -4, LINE_AA, 0); //caso seja a primeira posi��o, desenha uma bola vermelha, para identificar a posi��o inicial
			}
			if (i == vectorSize - 1) {
				circle(frameInicial, pieceMovesPoints[i], 5, Scalar(150, 255, 0), -4, LINE_AA, 0); //caso seja a ultima posi��o, desenha uma bola azulada, para identificar a posi��o final
			}
		}
	}

	if (id <= 15) {			//caso seja do time branco, identifica no nome do arquivo a ser gerado
		team = "White_";
	}
	else {					//caso seja do time preto, identifica no nome do arquivo a ser gerado
		team = "Black_";
	}

	convert << team << name << "_" << id << ".jpg";
	imwrite(convert.str(), frameInicial);  //cria um arquivo com o heatmap da pe�a identificada em formato .jpg
}


