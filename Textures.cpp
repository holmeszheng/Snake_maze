#include "Textures.h"

//scene textures

//整图纹理
CTexture texture_fixp1;
CTexture texture_fixp2;
CTexture texture_fixp3;
CTexture texture_fixp4;
CTexture texture_fixp6;
CTexture texture_fixp7;
CTexture texture_fixp8;

//箭头纹理
CTexture texture_arrowW1;
CTexture texture_arrowW2;
CTexture texture_arrowB1;
CTexture texture_arrowB2;

//level textures
CTexture texture_ground;
CTexture texture_head;
CTexture texture_body;
CTexture texture_cookies;
CTexture texture_fruit_N;
CTexture texture_fruit_L;
CTexture texture_fruit_C;
CTexture texture_fruit_D;
CTexture texture_fruit_A;
CTexture texture_background;
CTexture texture_barrier;
CTexture texture_border;

//在Loading_I中加载
void LoadfixedPictures()		//fixp1在setup中加载
{
	texture_fixp2.LoadFromFile("Pictures/Initial.jpg");
	texture_fixp3.LoadFromFile("Pictures/select.jpg");
	texture_fixp4.LoadFromFile("Pictures/loading_E.jpg");
	texture_fixp6.LoadFromFile("Pictures/loading_D.jpg");
	texture_fixp7.LoadFromFile("Pictures/gameover.jpg");
	texture_fixp8.LoadFromFile("Pictures/level_cleared.jpg");

	texture_arrowW1.LoadFromFile("Pictures/arrowW1.jpg");
	texture_arrowW2.LoadFromFile("Pictures/arrowW2.jpg");
	texture_arrowB1.LoadFromFile("Pictures/arrowB1.jpg");
	texture_arrowB2.LoadFromFile("Pictures/arrowB2.jpg");

}

//PHOTO PATH
char *photo_path0="Pictures/ground1.jpg";
char *photo_path1="Pictures/ground2.jpg";
char *photo_path2="Pictures/ground3.jpg";
char *photo_path3="Pictures/ground4.jpg";
char *photo_path4="Pictures/ground5.jpg";

char *photo_path5="Pictures/head1.jpg";
char *photo_path6="Pictures/head2.jpg";
char *photo_path7="Pictures/head3.jpg";
char *photo_path8="Pictures/head4.jpg";
char *photo_path9="Pictures/head5.jpg";

char *photo_path10="Pictures/body1.jpg";
char *photo_path11="Pictures/body2.jpg";
char *photo_path12="Pictures/body3.jpg";
char *photo_path13="Pictures/body4.jpg";
char *photo_path14="Pictures/body5.jpg";

char *photo_path15="Pictures/cookies1.jpg";
char *photo_path16="Pictures/cookies2.jpg";
char *photo_path17="Pictures/cookies3.jpg";
char *photo_path18="Pictures/cookies4.jpg";
char *photo_path19="Pictures/cookies5.jpg";

char *photo_path20="Pictures/fruit_N1.jpg";
char *photo_path21="Pictures/fruit_N2.jpg";
char *photo_path22="Pictures/fruit_N3.jpg";
char *photo_path23="Pictures/fruit_N4.jpg";
char *photo_path24="Pictures/fruit_N5.jpg";

char *photo_path25="Pictures/fruit_L1.jpg";
char *photo_path26="Pictures/fruit_L2.jpg";
char *photo_path27="Pictures/fruit_L3.jpg";
char *photo_path28="Pictures/fruit_L4.jpg";
char *photo_path29="Pictures/fruit_L5.jpg";

char *photo_path30="Pictures/fruit_D1.jpg";
char *photo_path31="Pictures/fruit_D2.jpg";
char *photo_path32="Pictures/fruit_D3.jpg";
char *photo_path33="Pictures/fruit_D4.jpg";
char *photo_path34="Pictures/fruit_D5.jpg";

char *photo_path35="Pictures/background1.jpg";
char *photo_path36="Pictures/background2.jpg";
char *photo_path37="Pictures/background3.jpg";
char *photo_path38="Pictures/background4.jpg";
char *photo_path39="Pictures/background5.jpg";

char *photo_path40="Pictures/barrier1.jpg";
char *photo_path41="Pictures/barrier2.jpg";
char *photo_path42="Pictures/barrier3.jpg";
char *photo_path43="Pictures/barrier4.jpg";
char *photo_path44="Pictures/barrier5.jpg";

char *photo_path45="Pictures/border1.jpg";
char *photo_path46="Pictures/border2.jpg";
char *photo_path47="Pictures/border3.jpg";
char *photo_path48="Pictures/border4.jpg";
char *photo_path49="Pictures/border5.jpg";

char *photo_path50="Pictures/fruit_C1.jpg";
char *photo_path51="Pictures/fruit_C2.jpg";
char *photo_path52="Pictures/fruit_C3.jpg";
char *photo_path53="Pictures/fruit_C4.jpg";
char *photo_path54="Pictures/fruit_C5.jpg";

char *photo_path55="Pictures/fruit_A1.jpg";
char *photo_path56="Pictures/fruit_A2.jpg";
char *photo_path57="Pictures/fruit_A3.jpg";
char *photo_path58="Pictures/fruit_A4.jpg";
char *photo_path59="Pictures/fruit_A5.jpg";