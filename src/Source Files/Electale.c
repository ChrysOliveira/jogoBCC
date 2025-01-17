#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "../Header Files/Electale.h"
#include "../Header Files/Personagem.h"
#include "../Header Files/Monstro.h"
#include "../Header Files/Menu.h"

void removeComponentes(ALLEGRO_DISPLAY* display,Personagem* personagem,ALLEGRO_EVENT_QUEUE* queue,ALLEGRO_TIMER* timer, Mapa mapa, Monstro * monstros) {
	al_uninstall_keyboard();
	al_destroy_display(display);
	al_destroy_bitmap(personagem->personagemCima);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	liberaMapa(&mapa);
	desalocaMonstros(monstros);
}

void registraEventosNaFila(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
}


void venceu(ALLEGRO_BITMAP* Venceu) {
		al_flip_display();

		al_draw_scaled_bitmap(venceu, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);

}

int verificarPlacar(Mapa* mapa, int posicaoX, int posicaoY) {
	int x = posicaoY / 40;
	int y = posicaoX / 40;
	int cont = 0;

	if (mapa->matriz[x][y] == VERIFICAR) {
		for (int i = 0; i <= 5; i++) {
			if (mapa->matriz[0][i] != PLACAR) {
				cont++;
			}
		}
		if (cont == 6) {
			return 1;
		}
	}
	return 0;
}


int main() {
	Personagem personagem;
	Mapa mapa;
	Monstro monstros;
	ALLEGRO_BITMAP* bitmapMapa;
	ALLEGRO_BITMAP* bitmapChao;
	ALLEGRO_BITMAP* bitmapParede;
	ALLEGRO_BITMAP* bitmapPorta;
	ALLEGRO_BITMAP* bitmapDica;
	ALLEGRO_BITMAP* bitmapPoder;
	ALLEGRO_BITMAP* bitmapPlacar;
	ALLEGRO_BITMAP* bitmapPlacarL;
	ALLEGRO_BITMAP* bitmapPlacarI;
	ALLEGRO_BITMAP* bitmapPlacarB;
	ALLEGRO_BITMAP* bitmapPlacarR;
	ALLEGRO_BITMAP* bitmapPlacarA;
	ALLEGRO_BITMAP* bitmapPlacarS;
	ALLEGRO_BITMAP* bitmapPergunta;
	ALLEGRO_BITMAP* bitmapVenceu;
	ALLEGRO_BITMAP* bitmapderrota;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* filaEventos;
	ALLEGRO_TIMER* timer;
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_BITMAP* fundo;
	ALLEGRO_FONT* fonte = NULL;

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();

	srand(time(0));

	display = al_create_display(1280, 960);

	filaEventos = al_create_event_queue();

	timer = al_create_timer(1 / 30.0);
	al_start_timer(timer);

	personagem.personagemBaixo = al_load_bitmap("../../assets/bitmaps/personagemBaixo.png");
	personagem.personagemCima = al_load_bitmap("../../assets/bitmaps/personagemCima.png");
	personagem.personagemEsquerda = al_load_bitmap("../../assets/bitmaps/personagemEsquerda.png");
	personagem.personagemDireita = al_load_bitmap("../../assets/bitmaps/personagemDireita.png");
	personagem.personagemPosicaoX = 40;
	personagem.personagemPosicaoY = 40;
	personagem.direcaoBitmap = 1;
	personagem.estaComPoder = 0;

	bitmapChao = al_load_bitmap("../../assets/bitmaps/chao.png");
	bitmapParede = al_load_bitmap("../../assets/bitmaps/parede.png");
	bitmapPorta = al_load_bitmap("../../assets/bitmaps/porta.png");
	bitmapDica = al_load_bitmap("../../assets/bitmaps/dica.png");
	bitmapPoder = al_load_bitmap("../../assets/bitmaps/poder.png");
	bitmapPlacar = al_load_bitmap("../../assets/bitmaps/placar.png");
	bitmapPlacarL = al_load_bitmap("../../assets/bitmaps/L.png");
	bitmapPlacarI = al_load_bitmap("../../assets/bitmaps/I.png");
	bitmapPlacarB = al_load_bitmap("../../assets/bitmaps/B.png");
	bitmapPlacarR = al_load_bitmap("../../assets/bitmaps/R.png");
	bitmapPlacarA = al_load_bitmap("../../assets/bitmaps/A.png");
	bitmapPlacarS = al_load_bitmap("../../assets/bitmaps/S.png");
	fundo = al_load_bitmap("../../assets/bitmaps/menuImg.png");
	fonte = al_load_font("../../assets/fonte/fonte.ttf", 48, 0);


	bitmapPergunta = al_load_bitmap("../../assets/bitmaps/pergunta_final.png");
	bitmapVenceu = al_load_bitmap("../../assets/bitmaps/tela_vitoria.jpg");
	bitmapderrota = al_load_bitmap("../../assets/bitmaps/tela_derrota.jpg");

	leMapa(&mapa);
	registraEventosNaFila(filaEventos, display, timer);

	int qntMonstros = quantidadeMonstros(&mapa);
	alocaMonstros(&monstros, qntMonstros);
	localizaMonstros(&mapa, &monstros, qntMonstros);



	int game = 0;
	int tempoComPoder = 0;
	while (1) {

		if (game == 0)
		{
			desenhaMenu(fundo, fonte);
			al_flip_display();

			while (1)
			{
				ALLEGRO_EVENT evento;

				al_get_keyboard_state(&keyboardState);
				al_wait_for_event(filaEventos, &evento);

				if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					exit(1);
				}

				registraEventosNaFila(filaEventos, display, timer);

				if (al_key_down(&keyboardState, ALLEGRO_KEY_ENTER))
				{
					game = 1;
					desenhaMapa(&mapa, bitmapChao, bitmapParede,
						bitmapPorta, bitmapDica, bitmapPoder,
						bitmapPlacar, bitmapPlacarL,
						bitmapPlacarI, bitmapPlacarB,
						bitmapPlacarR, bitmapPlacarA, bitmapPlacarS);

					desenhaPersonagem(&personagem, personagem.personagemPosicaoX, personagem.personagemPosicaoY, personagem.direcaoBitmap);
					desenhaMonstros(&monstros, qntMonstros);

					break;
				}

				if (al_key_down(&keyboardState, ALLEGRO_KEY_E))
				{
					exit(1);
				}
			}
		}

		al_flip_display();

		ALLEGRO_EVENT evento;

		al_wait_for_event(filaEventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			removeComponentes(display, &personagem, filaEventos, timer, mapa, &monstros);
			exit(1);
		}

		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			desenhaMapa(&mapa, bitmapChao,
				bitmapParede, bitmapPorta,
				bitmapDica, bitmapPoder,
				bitmapPlacar, bitmapPlacarL,
				bitmapPlacarI, bitmapPlacarB,
				bitmapPlacarR, bitmapPlacarA, bitmapPlacarS);

			al_get_keyboard_state(&keyboardState);
			movimenta(&mapa, keyboardState, &personagem, bitmapChao);
			movimentaMonstros(&mapa,&monstros,qntMonstros);
			
			if(ehPoder(&mapa,personagem.personagemPosicaoX,personagem.personagemPosicaoY))
			{
				desenhaChao(&mapa,personagem.personagemPosicaoX, personagem.personagemPosicaoY);
				personagem.estaComPoder = 1;
			}
			
			if(ehMonstro(&mapa,personagem.personagemPosicaoX,personagem.personagemPosicaoY))
			{
				if(personagem.estaComPoder == 0)
				{
					personagem.personagemPosicaoX = 40;
					personagem.personagemPosicaoY = 40;
					game = 0;
					while (1) {

						al_flip_display();

						al_draw_scaled_bitmap(bitmapderrota, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);
						al_get_keyboard_state(&keyboardState);
						al_wait_for_event(filaEventos, &evento);

						registraEventosNaFila(filaEventos, display, timer);
						if (al_key_down(&keyboardState, ALLEGRO_KEY_R))
						{
							personagem.personagemPosicaoX = 40;
							personagem.personagemPosicaoY = 40;
							leMapa(&mapa);
							game = 0;
							break;
						}
					}
				}
			}

			if(personagem.estaComPoder)
			{
				tempoComPoder++;
			}

			if(tempoComPoder == 300)
			{
				personagem.estaComPoder = 0;
				tempoComPoder = 0;
			}

			if (verificarPlacar(&mapa, personagem.personagemPosicaoX, personagem.personagemPosicaoY)){
				while (1) {
					al_flip_display();

					al_draw_scaled_bitmap(bitmapPergunta, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);

					al_get_keyboard_state(&keyboardState);
					al_wait_for_event(filaEventos, &evento);

					registraEventosNaFila(filaEventos, display, timer);

					if (al_key_down(&keyboardState, ALLEGRO_KEY_B))
					{
						while (1) {
							al_flip_display();

							al_draw_scaled_bitmap(bitmapVenceu, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);
							al_get_keyboard_state(&keyboardState);
							al_wait_for_event(filaEventos, &evento);

							registraEventosNaFila(filaEventos, display, timer);
							if(al_key_down(&keyboardState, ALLEGRO_KEY_R))							
							{
								personagem.personagemPosicaoX = 40;
								personagem.personagemPosicaoY = 40;
								leMapa(&mapa);
								game = 0;
								break;
							}
						}
						break;
					}
					

					if (al_key_down(&keyboardState, ALLEGRO_KEY_A))
					{
						while (1) {

							al_flip_display();

						al_draw_scaled_bitmap(bitmapderrota, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);
						al_get_keyboard_state(&keyboardState);
						al_wait_for_event(filaEventos, &evento);

						registraEventosNaFila(filaEventos, display, timer);
						if (al_key_down(&keyboardState, ALLEGRO_KEY_R))
							{
							personagem.personagemPosicaoX = 40;
							personagem.personagemPosicaoY = 40;
							leMapa(&mapa);
							game = 0;
							break;
							}
						}
						break;
					}
						 
					
					if (al_key_down(&keyboardState, ALLEGRO_KEY_C))
					{

						while (1) {

						al_flip_display();

						al_draw_scaled_bitmap(bitmapderrota, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);
						al_get_keyboard_state(&keyboardState);
						al_wait_for_event(filaEventos, &evento);

						registraEventosNaFila(filaEventos, display, timer);
						if (al_key_down(&keyboardState, ALLEGRO_KEY_R))
							{
							personagem.personagemPosicaoX = 40;
							personagem.personagemPosicaoY = 40;
							leMapa(&mapa);
							game = 0;
								break;
							}
						}
						break;
					}

					
			

					if (al_key_down(&keyboardState, ALLEGRO_KEY_D)) {

						while (1) {

							al_flip_display();

						al_draw_scaled_bitmap(bitmapderrota, 0, 0, 1280, 960, 0, 0, 1280, 960, 0);
						al_get_keyboard_state(&keyboardState);
						al_wait_for_event(filaEventos, &evento);

						registraEventosNaFila(filaEventos, display, timer);
						if (al_key_down(&keyboardState, ALLEGRO_KEY_R))
							{
							personagem.personagemPosicaoX = 40;
							personagem.personagemPosicaoY = 40;
							leMapa(&mapa);
							game = 0;
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
}

