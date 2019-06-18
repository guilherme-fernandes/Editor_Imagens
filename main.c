#include "Projeto_Final.h"

int main () {

	int opc, zoom,option;
	Img img_in;

	system ("clear");
	abre_img (&img_in);
	system ("clear");

	printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Salvar Imagem\n");
	printf("                2 - Preto e Branco\n");
	printf("                3 - Rotacionar\n");
	printf("                4 - Ampliar\n");
	printf("                5 - Reduzir\n");
	printf("                6 - Efeito de Blurring\n");
	printf("                7 - Efeito de Sharpening\n");
	printf("                8 - Efeito de Detecção de Bordas\n");
	printf("                9 - Abrir Nova Imagem\n");
	scanf ("%d", &option);
	system ("clear");
	while (option != Sair) {
	switch (option)
	{
		case Salvar :
		salva_img(&img_in);
		break;

		case PeB:
		grayscale (&img_in);
		break;

		case Rot:
		printf("Digite a direção: (1 para 90°/Esquerda, 2 para 90°/Direita, 3 para 180°)\n");
		scanf ("%d", &opc);
		rotaciona(&img_in, opc);
		break;

		case Amp:
		printf("Digite o tamanho do zoom: \n");
		scanf ("%d", &zoom);
		amplia(&img_in, zoom);
		break;

		case Red:
		printf("Digite o quanto quer reduzir sua imagem: \n");
		scanf ("%d", &zoom);
		reduz(&img_in, zoom);
		break;


		case Blur:
		blurring (&img_in);
		break;

		case Shar:
		sharpening (&img_in);
		break;

		case Detec:
		detecta_bordas (&img_in);
		break;

		case abre_nova:
		abrir_nova(&img_in);
		break;

		default :
		printf("Valor Inválido!\n");
		break;
	}

	printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Salvar Imagem\n");
	printf("                2 - Preto e Branco\n");
	printf("                3 - Rotacionar\n");
	printf("                4 - Ampliar\n");
	printf("                5 - Reduzir\n");
	printf("                6 - Efeito de Blurring\n");
	printf("                7 - Efeito de Sharpening\n");
	printf("                8 - Efeito de Detecção de Bordas\n");
	printf("                9 - Abrir Nova Imagem\n");
	scanf ("%d", &option);
	system ("clear");
}

	return 0;
	
}