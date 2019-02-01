// Projeto seletivo do voxar, Heat Map Analytics, feito pelo aluno : Gustavo Camargo Rocha Lima
//  3.3cm cada marcador

#include "ArucoMarkers.h"
#include "ChessPiece.h"
#include "VideoSave.h"


using namespace cv;
using namespace std;

int main(int argv, char** argc)
{
	bool gameStart = false;		//flag para inicio de partida
	int countFrames = 0;
	int turn;
	//double t_assist;

	ArucoMarkers markers = ArucoMarkers();
	//markers.createArucoMarkers();		//cria os marcadores para serem impressos

	//inicializa as peças de xadrez, salvando cada um no vetor abaixo
	vector<ChessPiece> chessPieces;
	for (int i = 0; i < 32; i++) {
		chessPieces.push_back(ChessPiece(i));
	}

	//inicializa a captura da imagem da webcam externa(source = 1)
	VideoSave video = VideoSave(1);
	Mat frameInitial;

	while (!video.endGame) {
		video.getFrame(); // salva uma imagem
		rectangle(video.frame, Point2f(0, 0), Point2f(700, 40), Scalar(255, 255, 255), -1, 8, 0);     // cria planos de fundo para uma melhor exibição
		rectangle(video.frame, Point2f(700, 40), Point2f(480, 700), Scalar(255, 255, 255), -1, 8, 0); // dos feedbacks de tempo,fps e placar de movimentos
		putText(video.frame, "VOXAR", Point2f(490, 22), FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 0, 0), 1, LINE_AA, 0);
		putText(video.frame, "   Chess", Point2f(490, 50), FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 0, 0), 1, LINE_AA, 0);
		char key = (char)waitKey(30); 
		

		if (!gameStart) {
			if (key == 105) {  //apertar a tecla i para iniciar a partida
				video.startTimer(); //inicia o tempo de partida
				turn = markers.detectAruco(video.frame, chessPieces, gameStart); //detecta as peças de xadrez para a captura das posições iniciais
				video.frame.copyTo(frameInitial);  //captura o frame inicial da partida com as posições iniciais das peças
				gameStart = true;		  		   //flag para inicio de jogo
			}
		}
		else {
			countFrames++;
			video.getFps(countFrames);
			video.updateTimer(turn);  // atualiza o tempo de partida
		}
		turn = markers.detectAruco(video.frame, chessPieces, gameStart); // detecta os marcadores na imagem e os identifica com os respectivos nomes e times das peças
		if (turn == 1) {
			video.timeAssistance();
		}
		video.printFps(video.frame); 
		video.printTimer(video.frame);	
		imshow("Webcam", video.frame);		//retorna o feedback da partida
		if (key == 102) {	//apertar a tecla f para finalizar a partida
			video.endGame = true;
			video.gameOver(frameInitial, chessPieces);
			break;
		}
	}
	return 0;
}


