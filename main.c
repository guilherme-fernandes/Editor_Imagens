#include "Projeto_Final.h"

int main () {

	int option, opc, zoom;
	Img img_in;

	abre_img (&img_in);


	printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Preto e Branco\n");
	printf("                2 - Blurring\n");
	printf("                3 - Sharpening\n");
	printf("                4 - Rotacionar\n");
	printf("                5 - Ampliar\n");
	printf("                6 - Reduzir\n");
	printf("                7 - Salvar Imagem\n");
	scanf ("%d", &option);

	while (option != 0) {
	switch (option)
	{
		case 1 :
		grayscale(&img_in);
		break;

	/*	case 2:
		blurring();
		break;

		case 3:
		sharpening();
		break;*/

		case 4:
		printf("Digite a direção: (1 para 90°/Esquerda, 2 para 90°/Direita, 3 para 180°)\n");
		scanf ("%d", &opc);
		rotaciona(&img_in, opc);
		break;

		case 5:
		printf("Digite o tamanho do zoom: \n");
		scanf ("%d", &zoom);
		amplia(&img_in, zoom);
		break;


		case 6:
		printf("Digite o quanto quer reduzir sua imagem: \n");
		scanf ("%d", &zoom);
		reduz(&img_in, zoom);
		break;

		case 7:
		salva_img(&img_in);
		break;

		default :
		printf("Valor Inválido!\n");
		break;
	}

		printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Preto e Branco\n");
	printf("                2 - Blurring\n");
	printf("                3 - Sharpening\n");
	printf("                4 - Rotacionar\n");
	printf("                5 - Ampliar\n");
	printf("                6 - Reduzir\n");
	printf("                7 - Salvar Imagem\n");
	scanf ("%d", &option);

}

	return 0;
}