#include <allegro.h>

// DECLARACOES INICIAIS //
int sair=0; void sair_allegro() {sair=1;}; 
int timer=0; void tempo() {timer++;};
int Ctrl_FPS=60; float delay=0;
void tint_bitmap(BITMAP *bmp,int color);

// INICIALIZACAO ALLEGRO //
int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse(); 
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_int_ex(tempo, BPS_TO_TIMER(60)); //60fps
  set_window_title("ALLEGRO MINIMAL");
  set_close_button_callback( sair_allegro );
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  BITMAP *buffer = create_bitmap(640,480);
	
	// Declaração de variáveis
  int x, y;
  int Pal0found, Pal1found, Pal2found, Pal3found, Pal4found, Pal5found, Pal6found, Pal7found, Pal8found;
  Pal0found = Pal1found = Pal2found = Pal3found = Pal4found = Pal5found = Pal6found = Pal7found = Pal8found = 1;
	int Palletefound=1;
	int ModoFullscreen=0;
	int ArrayPallete[32][4];
	int r=0, g=0, b=0, ValorDeCor=0;
	int CorNum=0;
	int podeatualizar=1;
	int AtualizaSlotPallete=0;
	int SlotNum=0;
	int ATUALIZA_S0=0; int ATUALIZA_S1=0; int ATUALIZA_S2=0; int ATUALIZA_S3=0;
	int ATUALIZA_S4=0; int ATUALIZA_S5=0; int ATUALIZA_S6=0; int ATUALIZA_S7=0;
	int ATUALIZA_S8=0; int GERAR_NOVA_PALETA=0;
	int Slot0OK=0; int Slot1OK=0; int Slot2OK=0; int Slot3OK=0;
	int Slot4OK=0; int Slot5OK=0; int Slot6OK=0; int Slot7OK=0; 
	int Slot8OK=0;
	
	for(y = 0; y < 4; y++) {
   	for(x = 0; x < 32; x++) {
			ArrayPallete[x][y]=0; //zera o array
		};
	};
	
	// Declaração de Bitmaps
	BITMAP *bmp;
	BITMAP *SlotPallete = create_bitmap(32,10);
	SlotPallete = load_bitmap("pallete.pcx", NULL); if (!SlotPallete) { Palletefound=0; };
	if(Palletefound==0){
		bmp = create_sub_bitmap(screen, 0, 0, 32, 10); 
		clear_to_color(bmp, makecol(255, 000, 255)); 
		save_bitmap("pallete.pcx", bmp, NULL);
		SlotPallete = load_bitmap("pallete.pcx", NULL); 
	};
	BITMAP *SlotPalleteDisplay = create_bitmap(256,80);
	BITMAP *EditorBackground = load_bitmap("system/EditorBackground.pcx", NULL);
	BITMAP *SlotVazio = load_bitmap("system/SlotVazio.pcx", NULL);
	BITMAP *StatusOK  = load_bitmap("system/StatusOK.pcx", NULL);
	BITMAP *StripPal0 = create_bitmap(32,1); clear_to_color(StripPal0, makecol(255, 000, 255)); 
	BITMAP *StripPal1 = create_bitmap(32,1); clear_to_color(StripPal1, makecol(255, 000, 255));
	BITMAP *StripPal2 = create_bitmap(32,1); clear_to_color(StripPal2, makecol(255, 000, 255));
	BITMAP *StripPal3 = create_bitmap(32,1); clear_to_color(StripPal3, makecol(255, 000, 255));
	BITMAP *StripPal4 = create_bitmap(32,1); clear_to_color(StripPal4, makecol(255, 000, 255));
	BITMAP *StripPal5 = create_bitmap(32,1); clear_to_color(StripPal5, makecol(255, 000, 255));
	BITMAP *StripPal6 = create_bitmap(32,1); clear_to_color(StripPal6, makecol(255, 000, 255));
	BITMAP *StripPal7 = create_bitmap(32,1); clear_to_color(StripPal7, makecol(255, 000, 255));
	BITMAP *StripPal8 = create_bitmap(32,1); clear_to_color(StripPal8, makecol(255, 000, 255));
	BITMAP *Slot0 = load_bitmap("pal0.pcx", NULL); if (!Slot0) { Pal0found=0; };
	BITMAP *Slot1 = load_bitmap("pal1.pcx", NULL); if (!Slot1) { Pal1found=0; };
	BITMAP *Slot2 = load_bitmap("pal2.pcx", NULL); if (!Slot2) { Pal2found=0; };
	BITMAP *Slot3 = load_bitmap("pal3.pcx", NULL); if (!Slot3) { Pal3found=0; };
	BITMAP *Slot4 = load_bitmap("pal4.pcx", NULL); if (!Slot4) { Pal4found=0; };
	BITMAP *Slot5 = load_bitmap("pal5.pcx", NULL); if (!Slot5) { Pal5found=0; };
	BITMAP *Slot6 = load_bitmap("pal6.pcx", NULL); if (!Slot6) { Pal6found=0; };
	BITMAP *Slot7 = load_bitmap("pal7.pcx", NULL); if (!Slot7) { Pal7found=0; };
	BITMAP *Slot8 = load_bitmap("pal8.pcx", NULL); if (!Slot8) { Pal8found=0; };
  
  // LOOP DE JOGO // 
  while (sair==0)
  { 
	
	delay=timer; clear_to_color(buffer,makecol(100,149,237)); if (key[KEY_ESC]) {sair=1;}; 
	
	/* < INICIO > */
	
	if (ModoFullscreen==0 and key[KEY_ALT] and key[KEY_ENTER]) {ModoFullscreen=1; set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);};
	if (ModoFullscreen==1 and key[KEY_ALT] and key[KEY_ENTER]) {ModoFullscreen=0; set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);};
	
	if(key[KEY_F1]){
	ATUALIZA_S0=1;
	ATUALIZA_S1=1;
	ATUALIZA_S2=1;
	ATUALIZA_S3=1;
	ATUALIZA_S4=1;
	ATUALIZA_S5=1;
	ATUALIZA_S6=1;
	ATUALIZA_S7=1;
	ATUALIZA_S8=1;
	GERAR_NOVA_PALETA=1;
	};
	
	if(ATUALIZA_S0==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot0->h; y++) { for(x = 0; x < Slot0->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot0, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot0, x, y); 
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot0->h; y++) { for(x = 0; x < Slot0->w; x++) { if(getpixel(Slot0, x, y) == makecol( r,g,b)){
		putpixel(Slot0, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal0, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S0=0; };
	
	if(ATUALIZA_S1==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot1->h; y++) { for(x = 0; x < Slot1->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot1, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot1, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot1->h; y++) { for(x = 0; x < Slot1->w; x++) { if(getpixel(Slot1, x, y) == makecol( r,g,b)){
		putpixel(Slot1, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal1, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S1=0; };
	
	if(ATUALIZA_S2==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot2->h; y++) { for(x = 0; x < Slot2->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot2, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot2, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot2->h; y++) { for(x = 0; x < Slot2->w; x++) { if(getpixel(Slot2, x, y) == makecol( r,g,b)){
		putpixel(Slot2, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal2, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S2=0; };
	
	if(ATUALIZA_S3==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot3->h; y++) { for(x = 0; x < Slot3->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot3, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot3, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot3->h; y++) { for(x = 0; x < Slot3->w; x++) { if(getpixel(Slot3, x, y) == makecol( r,g,b)){
		putpixel(Slot3, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal3, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S3=0; };
	
	if(ATUALIZA_S4==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot4->h; y++) { for(x = 0; x < Slot4->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot4, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot4, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot4->h; y++) { for(x = 0; x < Slot4->w; x++) { if(getpixel(Slot4, x, y) == makecol( r,g,b)){
		putpixel(Slot4, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal4, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S4=0; };
	
	if(ATUALIZA_S5==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot5->h; y++) { for(x = 0; x < Slot5->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot5, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot5, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot5->h; y++) { for(x = 0; x < Slot5->w; x++) { if(getpixel(Slot5, x, y) == makecol( r,g,b)){
		putpixel(Slot5, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal5, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S5=0; };
	
	if(ATUALIZA_S6==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot6->h; y++) { for(x = 0; x < Slot6->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot6, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot6, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot6->h; y++) { for(x = 0; x < Slot6->w; x++) { if(getpixel(Slot6, x, y) == makecol( r,g,b)){
		putpixel(Slot6, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal6, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S6=0; };
	
	if(ATUALIZA_S7==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot7->h; y++) { for(x = 0; x < Slot7->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot7, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot7, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot7->h; y++) { for(x = 0; x < Slot7->w; x++) { if(getpixel(Slot7, x, y) == makecol( r,g,b)){
		putpixel(Slot7, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal7, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S7=0; };
	
	if(ATUALIZA_S8==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot8->h; y++) { for(x = 0; x < Slot8->w; x++) { if(podeatualizar==1) {
		if(getpixel(Slot8, x, y) != makecol( 255,000,255)){ ValorDeCor = getpixel(Slot8, x, y);
		r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot8->h; y++) { for(x = 0; x < Slot8->w; x++) { if(getpixel(Slot8, x, y) == makecol( r,g,b)){
		putpixel(Slot8, x, y, makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		putpixel(StripPal8, i, 0, makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S8=0; };
	
	if(GERAR_NOVA_PALETA==1){
		blit(StripPal0, SlotPallete, 0, 0, 0, 0, 32, 1);
		blit(StripPal1, SlotPallete, 0, 0, 0, 1, 32, 1);
		blit(StripPal2, SlotPallete, 0, 0, 0, 2, 32, 1);
		blit(StripPal3, SlotPallete, 0, 0, 0, 3, 32, 1);
		blit(StripPal4, SlotPallete, 0, 0, 0, 4, 32, 1);
		blit(StripPal5, SlotPallete, 0, 0, 0, 5, 32, 1);
		blit(StripPal6, SlotPallete, 0, 0, 0, 6, 32, 1);
		blit(StripPal7, SlotPallete, 0, 0, 0, 7, 32, 1);
		blit(StripPal8, SlotPallete, 0, 0, 0, 8, 32, 1);
		save_bitmap("pallete.pcx", SlotPallete, NULL);
		if(Pal0found==1){ Slot0OK=1; };
		if(Pal1found==1){ Slot1OK=1; };
		if(Pal2found==1){ Slot2OK=1; };
		if(Pal3found==1){ Slot3OK=1; };
		if(Pal4found==1){ Slot4OK=1; };
		if(Pal5found==1){ Slot5OK=1; };
		if(Pal6found==1){ Slot6OK=1; };
		if(Pal7found==1){ Slot7OK=1; };
		if(Pal8found==1){ Slot8OK=1; };
	GERAR_NOVA_PALETA=0;
	};
	
//	if(key[KEY_F2]){
//	    Pal0found=1; BITMAP *Slot0 = load_bitmap("pal0.pcx", NULL); if (!Slot0) { Pal0found=0; };
//		Pal1found=1; BITMAP *Slot1 = load_bitmap("pal1.pcx", NULL); if (!Slot1) { Pal1found=0; };
//		Pal2found=1; BITMAP *Slot2 = load_bitmap("pal2.pcx", NULL); if (!Slot2) { Pal2found=0; };
//		Pal3found=1; BITMAP *Slot3 = load_bitmap("pal3.pcx", NULL); if (!Slot3) { Pal3found=0; };
//		Pal4found=1; BITMAP *Slot4 = load_bitmap("pal4.pcx", NULL); if (!Slot4) { Pal4found=0; };
//		Pal5found=1; BITMAP *Slot5 = load_bitmap("pal5.pcx", NULL); if (!Slot5) { Pal5found=0; };
//		Pal6found=1; BITMAP *Slot6 = load_bitmap("pal6.pcx", NULL); if (!Slot6) { Pal6found=0; };
//		Pal7found=1; BITMAP *Slot7 = load_bitmap("pal7.pcx", NULL); if (!Slot7) { Pal7found=0; };
//		Pal8found=1; BITMAP *Slot8 = load_bitmap("pal8.pcx", NULL); if (!Slot8) { Pal8found=0; };
//	};
		
	draw_sprite(buffer,EditorBackground,0,0);
  
	textprintf_centre_ex(buffer, font, 320,  20, makecol(255,255,255), -1, "HAMOOPI - PALLETE GENERATOR");
	textprintf_centre_ex(buffer, font, 320,  35, makecol(255,255,255), -1, "Aperte F1 para criar uma nova paleta");
	textprintf_centre_ex(buffer, font, 320,  45, makecol(255,255,255), -1, "Aperte ESC para sair");
	
	//desenha SlotPallete
	stretch_blit(SlotPallete, SlotPalleteDisplay, 
	0, 0, SlotPallete->w, SlotPallete->h, 
	0, 0, SlotPalleteDisplay->w, SlotPalleteDisplay->h);
	draw_sprite(buffer, SlotPalleteDisplay, 252, 91);
	
	//desenha slots
	if (Pal0found==0) { draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*0+0); };
	if (Pal1found==0) { draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*1+2); };
	if (Pal2found==0) { draw_sprite(buffer, SlotVazio, 64+128*1+2, 76+128*1+2); };
	if (Pal3found==0) { draw_sprite(buffer, SlotVazio, 64+128*2+4, 76+128*1+2); };
	if (Pal4found==0) { draw_sprite(buffer, SlotVazio, 64+128*3+6, 76+128*1+2); };
	if (Pal5found==0) { draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*2+4); };
	if (Pal6found==0) { draw_sprite(buffer, SlotVazio, 64+128*1+2, 76+128*2+4); };
	if (Pal7found==0) { draw_sprite(buffer, SlotVazio, 64+128*2+4, 76+128*2+4); };
	if (Pal8found==0) { draw_sprite(buffer, SlotVazio, 64+128*3+6, 76+128*2+4); };
	
	if (Pal0found==1) { draw_sprite(buffer, Slot0, 64+128*0+0, 76+128*0+0); };
	if (Pal1found==1) { draw_sprite(buffer, Slot1, 64+128*0+0, 76+128*1+2); };
	if (Pal2found==1) { draw_sprite(buffer, Slot2, 64+128*1+2, 76+128*1+2); };
	if (Pal3found==1) { draw_sprite(buffer, Slot3, 64+128*2+4, 76+128*1+2); };
	if (Pal4found==1) { draw_sprite(buffer, Slot4, 64+128*3+6, 76+128*1+2); };
	if (Pal5found==1) { draw_sprite(buffer, Slot5, 64+128*0+0, 76+128*2+4); };
	if (Pal6found==1) { draw_sprite(buffer, Slot6, 64+128*1+2, 76+128*2+4); };
	if (Pal7found==1) { draw_sprite(buffer, Slot7, 64+128*2+4, 76+128*2+4); };
	if (Pal8found==1) { draw_sprite(buffer, Slot8, 64+128*3+6, 76+128*2+4); };
	
	if (Slot0OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*0+0); };
	if (Slot1OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*1+2); };
	if (Slot2OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*1+2, 32+76+128*1+2); };
	if (Slot3OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*2+4, 32+76+128*1+2); };
	if (Slot4OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*3+6, 32+76+128*1+2); };
	if (Slot5OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*2+4); };
	if (Slot6OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*1+2, 32+76+128*2+4); };
	if (Slot7OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*2+4, 32+76+128*2+4); };
	if (Slot8OK==1) { draw_sprite(buffer, StatusOK, 32+64+128*3+6, 32+76+128*2+4); };
	
	//textos
	
	textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 76+128*0+0+116+1-110, makecol(000,000,000), -1, "LP");
	textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 76+128*0+0+116+0-110, makecol(255,255,255), -1, "LP");
	textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 212+1, makecol(000,000,000), -1, "MP");
	textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 212+0, makecol(255,255,255), -1, "MP");
	textprintf_right_ex(buffer, font, 122+128*1+0+66+1, 212+1, makecol(000,000,000), -1, "HP");
	textprintf_right_ex(buffer, font, 122+128*1+0+66+0, 212+0, makecol(255,255,255), -1, "HP");
	textprintf_right_ex(buffer, font, 122+128*2+0+68+1, 212+1, makecol(000,000,000), -1, "LK");
	textprintf_right_ex(buffer, font, 122+128*2+0+68+0, 212+0, makecol(255,255,255), -1, "LK");
	textprintf_right_ex(buffer, font, 122+128*3+0+70+1, 212+1, makecol(000,000,000), -1, "MK");
	textprintf_right_ex(buffer, font, 122+128*3+0+70+0, 212+0, makecol(255,255,255), -1, "MK");
	
	textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 130+212+1, makecol(000,000,000), -1, "HK");
	textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 130+212+0, makecol(255,255,255), -1, "HK");
	textprintf_right_ex(buffer, font, 122+128*1+0+66+1, 130+212+1, makecol(000,000,000), -1, "SELECT");
	textprintf_right_ex(buffer, font, 122+128*1+0+66+0, 130+212+0, makecol(255,255,255), -1, "SELECT");
	textprintf_right_ex(buffer, font, 122+128*2+0+68+1, 130+212+1, makecol(000,000,000), -1, "START");
	textprintf_right_ex(buffer, font, 122+128*2+0+68+0, 130+212+0, makecol(255,255,255), -1, "START");
	textprintf_right_ex(buffer, font, 122+128*3+0+70+1, 130+212+1, makecol(000,000,000), -1, "HOLD");
	textprintf_right_ex(buffer, font, 122+128*3+0+70+0, 130+212+0, makecol(255,255,255), -1, "HOLD");
	
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*0+0+116+1, makecol(000,000,000), -1, "pal0.pcx");
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*0+0+116+0, makecol(255,255,255), -1, "pal0.pcx");
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*1+0+118+1, makecol(000,000,000), -1, "pal1.pcx");
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*1+0+118+0, makecol(255,255,255), -1, "pal1.pcx");
	textprintf_centre_ex(buffer, font, 64+128*1+0+64+1, 76+128*1+0+118+1, makecol(000,000,000), -1, "pal2.pcx");
	textprintf_centre_ex(buffer, font, 64+128*1+0+64+0, 76+128*1+0+118+0, makecol(255,255,255), -1, "pal2.pcx");
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*1+0+118+1, makecol(000,000,000), -1, "pal3.pcx");
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*1+0+118+0, makecol(255,255,255), -1, "pal3.pcx");
	textprintf_centre_ex(buffer, font, 64+128*3+0+64+1, 76+128*1+0+118+1, makecol(000,000,000), -1, "pal4.pcx");
	textprintf_centre_ex(buffer, font, 64+128*3+0+64+0, 76+128*1+0+118+0, makecol(255,255,255), -1, "pal4.pcx");
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*2+0+120+1, makecol(000,000,000), -1, "pal5.pcx");
	textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*2+0+120+0, makecol(255,255,255), -1, "pal5.pcx");
	textprintf_centre_ex(buffer, font, 64+128*1+0+64+1, 76+128*2+0+120+1, makecol(000,000,000), -1, "pal6.pcx");
	textprintf_centre_ex(buffer, font, 64+128*1+0+64+0, 76+128*2+0+120+0, makecol(255,255,255), -1, "pal6.pcx");
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*2+0+120+1, makecol(000,000,000), -1, "pal7.pcx");
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*2+0+120+0, makecol(255,255,255), -1, "pal7.pcx");
	textprintf_centre_ex(buffer, font, 64+128*3+0+64+1, 76+128*2+0+120+1, makecol(000,000,000), -1, "pal8.pcx");
	textprintf_centre_ex(buffer, font, 64+128*3+0+64+0, 76+128*2+0+120+0, makecol(255,255,255), -1, "pal8.pcx");
	
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*0+0+102+1, makecol(000,000,000), -1, "pallete.pcx");
	textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*0+0+102+0, makecol(255,255,255), -1, "pallete.pcx");
	
	//DEBUG
	draw_sprite(buffer, StripPal0, 80, 30+3);
	draw_sprite(buffer, StripPal1, 80, 32+3);
	draw_sprite(buffer, StripPal2, 80, 34+3);
	draw_sprite(buffer, StripPal3, 80, 36+3);
	draw_sprite(buffer, StripPal4, 80, 38+3);
	draw_sprite(buffer, StripPal5, 80, 40+3);
	draw_sprite(buffer, StripPal6, 80, 42+3);
	draw_sprite(buffer, StripPal7, 80, 44+3);
	draw_sprite(buffer, StripPal8, 80, 46+3);
	
	draw_sprite(screen, buffer, 0, 0);
		
  // FINALIZACOES //
	while(timer==delay){};	
	clear(buffer);
  }; 
  destroy_bitmap(buffer);
  return 0;
};
END_OF_MAIN();


//Pallete Editor by Daniel Moura - danielmouradesigner@gmail.com - 16/03/2019


