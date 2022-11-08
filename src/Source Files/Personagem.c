#include <allegro5/allegro.h>
#include "../Header Files/Personagem.h"

void movimenta(Mapa* mapa, ALLEGRO_KEYBOARD_STATE keyboardState, Personagem* personagem, ALLEGRO_BITMAP * bitmapChao) {

	int x = personagem->personagemPosicaoX / 40;
	int y = personagem->personagemPosicaoY / 40;
	
	if (al_key_down(&keyboardState, ALLEGRO_KEY_UP)) {
		
		if (!ehParede(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY - 1)) {
			personagem->personagemPosicaoY -= 10;
		}

		desenhaPersonagem(personagem, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

		ehDica(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
		ehPoder(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
	
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_DOWN)) {

		if (!ehParede(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY + 41)) {
			personagem->personagemPosicaoY += 10;
		}
		
		desenhaPersonagem(personagem, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

		ehDica(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
		ehPoder(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)) {

		if (!ehParede(mapa, personagem->personagemPosicaoX - 1, personagem->personagemPosicaoY)) {
			personagem->personagemPosicaoX -= 10;
		}
		
		desenhaPersonagem(personagem, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

		ehDica(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
		ehPoder(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)) {

		if (!ehParede(mapa, personagem->personagemPosicaoX + 41, personagem->personagemPosicaoY)) {
			personagem->personagemPosicaoX += 10;
		}
		
		desenhaPersonagem(personagem, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

		ehDica(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
		ehPoder(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
	}else
	{
		desenhaPersonagem(personagem, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

		ehDica(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);
		ehPoder(mapa, personagem->personagemPosicaoX, personagem->personagemPosicaoY);

	}
}

void desenhaPersonagem(Personagem * personagem, int posicaoX, int posicaoY) {
	al_draw_scaled_bitmap(personagem->personagemBitmap, 0, 0, 40, 40, posicaoX, posicaoY, 40, 40, 0);
}