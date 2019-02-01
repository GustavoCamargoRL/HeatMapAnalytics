#include "VideoSave.h"

VideoSave::VideoSave(int source) {
	timeStart = 0.0;
	time = 0.0;
	whiteTime = 0.0;
	blackTime = 0.0;
	whiteTimeAux = 0.0;
	blackTimeAux = 0.0;
	timeAssist = 0.0;
	team = 1;
	idSource = source;
	video.open(idSource);
	endGame = false;
	fps = 0;
}

void VideoSave::getFrame() {
	if (!video.isOpened()) {  //checa se o video esta sendo capturado
		endGame = true;
	}
	else {
		video.read(frame); //salva o frame atual do video
	}

	if (endGame) {
		video.release();	//fecha a webcam
	}
}

void VideoSave::getFps(int countFrames) {
	fps = (countFrames / time);  //calculo de frames por segundo 
}

void VideoSave::printFps(Mat& frame) {   //metodo para imprimir na tela o fps

	putText(frame, format("FPS: %d",fps), Point2f(300, 25), FONT_ITALIC, 0.8, Scalar(0, 0, 255), 1, LINE_AA);

}

void VideoSave::startTimer() {				

	timeStart = clock();
	timeAssist = clock();
}

void VideoSave::timeAssistance() {			//atualiza o tempo auxiliar do calculo dos tempos dos jogadores
	timeAssist = clock();
}

void VideoSave::updateTimer(bool turn) {

	time = (double)(clock() - timeStart) / 1000; //divide por 1000 para retornar valor em segundo

	if (turn) {
		team++;
	}
	if (team % 2 == 0) {						//seguindo a ordem de turnos, verifica se é a vez do time Preto
		blackTime = ((double)(clock() - timeAssist) / 1000) + blackTimeAux;		//calcula o tempo corrido que o time Preto teve de jogo
		whiteTimeAux = whiteTime;												//salva o tempo do ultimo turno do outro jogador
	}
	else if (team % 2 == 1) {										//team inicia em 1, já esperando que o time Branco comece
		whiteTime = ((double)(clock() - timeAssist) / 1000) + whiteTimeAux;		//calcula o tempo corrido que o time Branco teve de jogo
		blackTimeAux = blackTime;												//salva o tempo do ultimo turno do outro jogador
	}
}

void VideoSave::printTimer(Mat& frame) { //metodo para imprimir na tela o tempo de partida

	putText(frame, format("Tempo: %.1f s",time), Point2f(20, 25), FONT_ITALIC, 0.8, Scalar(0, 0, 255), 1, LINE_AA);				//imprime o tempo total de partida
	putText(frame, format("T Brancas:"), Point2f(490, 310), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);				//imprime o tempo de jogo do time Branco
	putText(frame, format(" %.1f s", whiteTime), Point2f(490, 335), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);
	putText(frame, format("T Pretas:"), Point2f(490, 365), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);				//imprime o tempo de jogo do time Preto
	putText(frame, format(" %.1f s", blackTime), Point2f(490, 395), FONT_ITALIC, 0.8, Scalar(100, 100, 100), 0.5, LINE_AA);



}

void VideoSave::gameOver(Mat& frame, vector<ChessPiece>& pieces) {
	//gera o heat map para cada peça
	for (int i = 0; i < pieces.size(); i++) {
		Mat heatMapFrame;  //matriz de apoio para gerar heat map de cada peça isolada
		frame.copyTo(heatMapFrame);  //copia o frame inicial da partida para a matriz de apoio
		pieces[i].heatMap(heatMapFrame);
	}
}

