#include "ArucoMarkers.h"

ArucoMarkers::ArucoMarkers(){
	//escolhe marcadores de tamanho 4x4 pixels de acordo com a biblioteca
	markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

}

void ArucoMarkers::createArucoMarkers() {
	Mat outputMarker;				//Matriz na qual os marcadores serão criados

	for (int i = 0; i < 32; i++) {  // criando 32 marcadores para servir como peças de xadrez
		aruco::drawMarker(markerDictionary, i, 125, outputMarker, 1); //Gera os marcadores com 125x125 pixels
		ostringstream convert;
		string imageName = "4x4Marker_";
		convert << imageName << i << ".jpg"; //salva o arquivo como uma imagem .jpg
		imwrite(convert.str(), outputMarker);

	}
}

bool ArucoMarkers::detectAruco(Mat& currentFrame, vector<ChessPiece>& allChessPieces, bool gameStart) {
	Point2f center;
	// Detecta todos os marcadores que estão na imagem atual de acordo com o dicionario escolhido, guardando as posicoes corners e o id de cada marcador
	aruco::detectMarkers(currentFrame, markerDictionary, corners, ids);

	if (ids.size() > 0) {
		turn = false;
		//aruco::drawDetectedMarkers(currentFrame, corners, ids);
		for (int i = 0; i < ids.size(); i++) {

			//localização do centro da peça para escrita do nome e identificação do time
			if (corners[i][0].x < corners[i][2].x) {		
				center.x = corners[i][0].x + ((abs(corners[i][2].x - corners[i][0].x)) / 2);
			}
			else {
				center.x = corners[i][2].x + ((abs(corners[i][2].x - corners[i][0].x)) / 2);
			}
			if (corners[i][0].y < corners[i][2].y) {
				center.y = corners[i][0].y + ((abs(corners[i][2].y - corners[i][0].y)) / 2);
			}
			else {
				center.y = corners[i][2].y + ((abs(corners[i][2].y - corners[i][0].y)) / 2);
			}
			// desenha um circulo no marcador indicando o time branco ou preto 
			circle(currentFrame, center, 22, Scalar(allChessPieces[ids[i]].B, allChessPieces[ids[i]].G, allChessPieces[ids[i]].R), -2, LINE_AA, 0);
			// escreve o nome da peça no marcador
			center.x = center.x - 20; //desloca o ponto central a fim de centralizar o nome dentro do circulo
			putText(currentFrame, allChessPieces[ids[i]].name, center, FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 120, 255), 1, LINE_AA);

			//encontra o centro do marcador a partir de 2 pontos "em diagonais"
			allChessPieces[ids[i]].centerCoord(corners[i][0], corners[i][2]);
			//salva a posicao da peca depois que o jogo foi iniciado
			if (gameStart) {
				move = allChessPieces[ids[i]].saveMoves();	
				if (move) {
					turn = true;
					if (allChessPieces[ids[i]].id <= 15) {		//caso o time branco tenha efetuado uma jogada aumenta o respectivo contador e aciona flag de turno
						whiteMoves++;
					}
					else {										//caso o time preto tenha efetuado uma jogada aumenta o respectivo contador e aciona flag de turno
						blackMoves++;
					}
				}
				//ao iniciar partida, exibe o placar de movimentação de cada time
				putText(currentFrame, format("Brancas:"), Point2f(490, 105), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);
				putText(currentFrame, format(" %d Moves", whiteMoves), Point2f(490, 130), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);
				putText(currentFrame, format("Pretas:"), Point2f(490, 160), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);
				putText(currentFrame, format(" %d Moves", blackMoves), Point2f(490, 190), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);
				
			}
			else {
				whiteMoves = 0;	//inicialização 
				blackMoves = 0;	//inicialização
			}
			
		}
	}
	return turn;

}