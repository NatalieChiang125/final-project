// Map.cpp
#include "map.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include <fstream>
#include <iostream>

PlayScene *Map::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
    
}

Map::Map() {
    /*loadMapFromFile(filepath);
    // 這裡可以載入圖片資源，音效等
    tileset = al_load_bitmap("tileset.png");
    coinSprites = al_load_bitmap("coin_sprites.png");
    // 其他初始化*/
    tiles = std::vector<std::vector<BlockType>>(
        PlayScene::MapHeight,
        std::vector<BlockType>(PlayScene::MapWidth, BlockType::FLOOR)
    );

    tileSet[0] = new Tile("play/Castle/Castle1.png", 0, 0);
    tileSet[1] = new Tile("play/grass.png", 0, 0);
    tileSet[2] = new Tile("play/sea.png", 0, 0);

    tileSet[3] = new Tile("play/playground/ground1.jpg", 0, 0);
    tileSet[4] = new Tile("play/playground/ground2.jpg", 0, 0);
    tileSet[5] = new Tile("play/playground/ground3.jpg", 0, 0);
    tileSet[6] = new Tile("play/playground/ground4.jpg", 0, 0);
    tileSet[7] = new Tile("play/playground/ground5.jpg", 0, 0);
    tileSet[8] = new Tile("play/playground/ground6.jpg", 0, 0);
    tileSet[9] = new Tile("play/playground/ground7.jpg", 0, 0);
    tileSet[10] = new Tile("play/playground/ground8.jpg", 0, 0);
    tileSet[11] = new Tile("play/playground/ground9.jpg", 0, 0);
    tileSet[12] = new Tile("play/playground/ground10.jpg", 0, 0);
    tileSet[13] = new Tile("play/playground/ground11.jpg", 0, 0);
    tileSet[14] = new Tile("play/playground/ground12.jpg", 0, 0);
    tileSet[15] = new Tile("play/playground/ground13.jpg", 0, 0);
    tileSet[16] = new Tile("play/playground/ground14.jpg", 0, 0);
    tileSet[17] = new Tile("play/playground/ground15.jpg", 0, 0);
    tileSet[18] = new Tile("play/playground/ground16.jpg", 0, 0);
    tileSet[19] = new Tile("play/playground/ground17.jpg", 0, 0);
    tileSet[20] = new Tile("play/playground/ground18.jpg", 0, 0);
    tileSet[21] = new Tile("play/playground/ground19.jpg", 0, 0);
    tileSet[22] = new Tile("play/playground/ground20.jpg", 0, 0);
    tileSet[23] = new Tile("play/playground/ground21.jpg", 0, 0);
    tileSet[24] = new Tile("play/playground/ground22.jpg", 0, 0);
    tileSet[25] = new Tile("play/playground/ground23.jpg", 0, 0);
    tileSet[26] = new Tile("play/playground/ground24.jpg", 0, 0);
    tileSet[27] = new Tile("play/playground/ground25.jpg", 0, 0);
    tileSet[28] = new Tile("play/playground/ground26.jpg", 0, 0);
    tileSet[29] = new Tile("play/playground/ground27.jpg", 0, 0);
    tileSet[30] = new Tile("play/playground/ground28.jpg", 0, 0);
    tileSet[31] = new Tile("play/playground/ground29.jpg", 0, 0);
    tileSet[32] = new Tile("play/playground/ground30.jpg", 0, 0);
    tileSet[33] = new Tile("play/playground/ground31.jpg", 0, 0);
    tileSet[34] = new Tile("play/playground/ground32.jpg", 0, 0);
    tileSet[35] = new Tile("play/playground/ground33.jpg", 0, 0);
    tileSet[36] = new Tile("play/playground/ground34.jpg", 0, 0);
    tileSet[37] = new Tile("play/playground/ground35.jpg", 0, 0);
    tileSet[168] = new Tile("play/playground/ground36.jpg", 0, 0);
    tileSet[169] = new Tile("play/playground/ground37.jpg", 0, 0);
    tileSet[170] = new Tile("play/playground/ground38.jpg", 0, 0);
    tileSet[171] = new Tile("play/playground/ground39.jpg", 0, 0);
    tileSet[172] = new Tile("play/playground/ground40.jpg", 0, 0);
    tileSet[173] = new Tile("play/playground/ground41.jpg", 0, 0);
    tileSet[174] = new Tile("play/playground/ground42.jpg", 0, 0);

    tileSet[38] = new Tile("play/CSbuilding/CSbuilding1.jpg", 0, 0);
    tileSet[39] = new Tile("play/CSbuilding/CSbuilding2.jpg", 0, 0);
    tileSet[40] = new Tile("play/CSbuilding/CSbuilding3.jpg", 0, 0);
    tileSet[41] = new Tile("play/CSbuilding/CSbuilding4.jpg", 0, 0);
    tileSet[42] = new Tile("play/CSbuilding/CSbuilding5.jpg", 0, 0);
    tileSet[43] = new Tile("play/CSbuilding/CSbuilding6.jpg", 0, 0);
    tileSet[44] = new Tile("play/CSbuilding/CSbuilding7.jpg", 0, 0);
    tileSet[45] = new Tile("play/CSbuilding/CSbuilding8.jpg", 0, 0);
    tileSet[46] = new Tile("play/CSbuilding/CSbuilding9.jpg", 0, 0);
    tileSet[47] = new Tile("play/CSbuilding/CSbuilding10.jpg", 0, 0);
    tileSet[48] = new Tile("play/CSbuilding/CSbuilding11.jpg", 0, 0);
    tileSet[49] = new Tile("play/CSbuilding/CSbuilding12.jpg", 0, 0);
    tileSet[50] = new Tile("play/CSbuilding/CSbuilding13.jpg", 0, 0);
    tileSet[51] = new Tile("play/CSbuilding/CSbuilding14.jpg", 0, 0);
    tileSet[52] = new Tile("play/CSbuilding/CSbuilding15.jpg", 0, 0);
    tileSet[53] = new Tile("play/CSbuilding/CSbuilding16.jpg", 0, 0);
    tileSet[54] = new Tile("play/CSbuilding/CSbuilding17.jpg", 0, 0);
    tileSet[55] = new Tile("play/CSbuilding/CSbuilding18.jpg", 0, 0);
    tileSet[56] = new Tile("play/CSbuilding/CSbuilding19.jpg", 0, 0);
    tileSet[57] = new Tile("play/CSbuilding/CSbuilding20.jpg", 0, 0);
    tileSet[58] = new Tile("play/CSbuilding/CSbuilding21.jpg", 0, 0);
    tileSet[59] = new Tile("play/CSbuilding/CSbuilding22.jpg", 0, 0);
    tileSet[60] = new Tile("play/CSbuilding/CSbuilding23.jpg", 0, 0);
    tileSet[61] = new Tile("play/CSbuilding/CSbuilding24.jpg", 0, 0);
    tileSet[62] = new Tile("play/CSbuilding/CSbuilding25.jpg", 0, 0);
    tileSet[63] = new Tile("play/CSbuilding/CSbuilding26.jpg", 0, 0);
    tileSet[64] = new Tile("play/CSbuilding/CSbuilding27.jpg", 0, 0);
    tileSet[65] = new Tile("play/CSbuilding/CSbuilding28.jpg", 0, 0);
    tileSet[66] = new Tile("play/CSbuilding/CSbuilding29.jpg", 0, 0);
    tileSet[67] = new Tile("play/CSbuilding/CSbuilding30.jpg", 0, 0);
    tileSet[68] = new Tile("play/CSbuilding/CSbuilding31.jpg", 0, 0);
    tileSet[69] = new Tile("play/CSbuilding/CSbuilding32.jpg", 0, 0);
    tileSet[70] = new Tile("play/CSbuilding/CSbuilding33.jpg", 0, 0);
    tileSet[71] = new Tile("play/CSbuilding/CSbuilding34.jpg", 0, 0);
    tileSet[72] = new Tile("play/CSbuilding/CSbuilding35.jpg", 0, 0);
    tileSet[73] = new Tile("play/CSbuilding/CSbuilding36.jpg", 0, 0);
    tileSet[74] = new Tile("play/CSbuilding/CSbuilding37.jpg", 0, 0);
    tileSet[75] = new Tile("play/CSbuilding/CSbuilding38.jpg", 0, 0);
    tileSet[76] = new Tile("play/CSbuilding/CSbuilding39.jpg", 0, 0);
    tileSet[77] = new Tile("play/CSbuilding/CSbuilding40.jpg", 0, 0);
    tileSet[78] = new Tile("play/CSbuilding/CSbuilding41.jpg", 0, 0);
    tileSet[79] = new Tile("play/CSbuilding/CSbuilding42.jpg", 0, 0);
    tileSet[80] = new Tile("play/CSbuilding/CSbuilding43.jpg", 0, 0);
    tileSet[81] = new Tile("play/CSbuilding/CSbuilding44.jpg", 0, 0);
    tileSet[82] = new Tile("play/CSbuilding/CSbuilding45.jpg", 0, 0);
    tileSet[83] = new Tile("play/CSbuilding/CSbuilding46.jpg", 0, 0);
    tileSet[84] = new Tile("play/CSbuilding/CSbuilding47.jpg", 0, 0);
    tileSet[85] = new Tile("play/CSbuilding/CSbuilding48.jpg", 0, 0);
    tileSet[86] = new Tile("play/CSbuilding/CSbuilding49.jpg", 0, 0);
    tileSet[87] = new Tile("play/CSbuilding/CSbuilding50.jpg", 0, 0);

    //tileSet[88] = new Tile("play/Lake/Lake0.jpg", 0, 0);
    tileSet[89] = new Tile("play/Lake/Lake1.jpg", 0, 0);
    tileSet[90] = new Tile("play/Lake/Lake2.jpg", 0, 0);
    tileSet[91] = new Tile("play/Lake/Lake3.jpg", 0, 0);
    tileSet[92] = new Tile("play/Lake/Lake4.jpg", 0, 0);
    tileSet[93] = new Tile("play/Lake/Lake5.jpg", 0, 0);
    tileSet[94] = new Tile("play/Lake/Lake6.jpg", 0, 0);
    tileSet[95] = new Tile("play/Lake/Lake7.jpg", 0, 0);
    tileSet[96] = new Tile("play/Lake/Lake8.jpg", 0, 0);
    tileSet[97] = new Tile("play/Lake/Lake9.jpg", 0, 0);
    tileSet[98] = new Tile("play/Lake/Lake10.jpg", 0, 0);
    tileSet[99] = new Tile("play/Lake/Lake11.jpg", 0, 0);
    tileSet[100] = new Tile("play/Lake/Lake12.jpg", 0, 0);
    tileSet[101] = new Tile("play/Lake/Lake13.jpg", 0, 0);
    tileSet[102] = new Tile("play/Lake/Lake14.jpg", 0, 0);
    tileSet[103] = new Tile("play/Lake/Lake15.jpg", 0, 0);
    tileSet[104] = new Tile("play/Lake/Lake16.jpg", 0, 0);
    tileSet[105] = new Tile("play/Lake/Lake17.jpg", 0, 0);
    tileSet[106] = new Tile("play/Lake/Lake18.jpg", 0, 0);
    tileSet[107] = new Tile("play/Lake/Lake19.jpg", 0, 0);
    tileSet[108] = new Tile("play/Lake/Lake20.jpg", 0, 0);
    tileSet[109] = new Tile("play/Lake/Lake21.jpg", 0, 0);
    tileSet[110] = new Tile("play/Lake/Lake22.jpg", 0, 0);
    tileSet[111] = new Tile("play/Lake/Lake23.jpg", 0, 0);
    tileSet[112] = new Tile("play/Lake/Lake24.jpg", 0, 0);
    tileSet[113] = new Tile("play/Lake/Lake25.jpg", 0, 0);
    /*tileSet[114] = new Tile("play/Lake/Lake26.jpg", 0, 0);
    tileSet[115] = new Tile("play/Lake/Lake27.jpg", 0, 0);
    tileSet[116] = new Tile("play/Lake/Lake28.jpg", 0, 0);
    tileSet[117] = new Tile("play/Lake/Lake29.jpg", 0, 0);
    tileSet[118] = new Tile("play/Lake/Lake30.jpg", 0, 0);*/

    tileSet[119] = new Tile("play/Library/LIBRARY1.jpg", 0, 0);
    tileSet[120] = new Tile("play/Library/LIBRARY2.jpg", 0, 0);
    tileSet[121] = new Tile("play/Library/LIBRARY3.jpg", 0, 0);
    tileSet[122] = new Tile("play/Library/LIBRARY4.jpg", 0, 0);
    tileSet[123] = new Tile("play/Library/LIBRARY5.jpg", 0, 0);
    tileSet[124] = new Tile("play/Library/LIBRARY6.jpg", 0, 0);
    tileSet[125] = new Tile("play/Library/LIBRARY7.jpg", 0, 0);
    tileSet[126] = new Tile("play/Library/LIBRARY8.jpg", 0, 0);
    tileSet[127] = new Tile("play/Library/LIBRARY9.jpg", 0, 0);
    tileSet[128] = new Tile("play/Library/LIBRARY10.jpg", 0, 0);
    tileSet[129] = new Tile("play/Library/LIBRARY11.jpg", 0, 0);
    tileSet[130] = new Tile("play/Library/LIBRARY12.jpg", 0, 0);
    tileSet[131] = new Tile("play/Library/LIBRARY13.jpg", 0, 0);
    tileSet[132] = new Tile("play/Library/LIBRARY14.jpg", 0, 0);
    tileSet[133] = new Tile("play/Library/LIBRARY15.jpg", 0, 0);
    tileSet[134] = new Tile("play/Library/LIBRARY16.jpg", 0, 0);
    tileSet[135] = new Tile("play/Library/LIBRARY17.jpg", 0, 0);
    tileSet[136] = new Tile("play/Library/LIBRARY18.jpg", 0, 0);
    tileSet[137] = new Tile("play/Library/LIBRARY19.jpg", 0, 0);
    tileSet[138] = new Tile("play/Library/LIBRARY20.jpg", 0, 0);
    tileSet[139] = new Tile("play/Library/LIBRARY21.jpg", 0, 0);
    tileSet[140] = new Tile("play/Library/LIBRARY22.jpg", 0, 0);
    tileSet[141] = new Tile("play/Library/LIBRARY23.jpg", 0, 0);
    tileSet[142] = new Tile("play/Library/LIBRARY24.jpg", 0, 0);
    tileSet[143] = new Tile("play/Library/LIBRARY25.jpg", 0, 0);
    tileSet[144] = new Tile("play/Library/LIBRARY26.jpg", 0, 0);
    tileSet[145] = new Tile("play/Library/LIBRARY27.jpg", 0, 0);
    tileSet[146] = new Tile("play/Library/LIBRARY28.jpg", 0, 0);
    tileSet[147] = new Tile("play/Library/LIBRARY29.jpg", 0, 0);
    tileSet[148] = new Tile("play/Library/LIBRARY30.jpg", 0, 0);
    tileSet[149] = new Tile("play/Library/LIBRARY31.jpg", 0, 0);
    tileSet[150] = new Tile("play/Library/LIBRARY32.jpg", 0, 0);
    tileSet[151] = new Tile("play/Library/LIBRARY33.jpg", 0, 0);
    tileSet[152] = new Tile("play/Library/LIBRARY34.jpg", 0, 0);
    tileSet[153] = new Tile("play/Library/LIBRARY35.jpg", 0, 0);
    tileSet[154] = new Tile("play/Library/LIBRARY36.jpg", 0, 0);
    tileSet[155] = new Tile("play/Library/LIBRARY37.jpg", 0, 0);
    tileSet[156] = new Tile("play/Library/LIBRARY38.jpg", 0, 0);
    tileSet[157] = new Tile("play/Library/LIBRARY39.jpg", 0, 0);
    tileSet[158] = new Tile("play/Library/LIBRARY40.jpg", 0, 0);
    tileSet[159] = new Tile("play/Library/LIBRARY41.jpg", 0, 0);
    tileSet[160] = new Tile("play/Library/LIBRARY42.jpg", 0, 0);
    tileSet[161] = new Tile("play/Library/LIBRARY43.jpg", 0, 0);
    tileSet[162] = new Tile("play/Library/LIBRARY44.jpg", 0, 0);
    tileSet[163] = new Tile("play/Library/LIBRARY45.jpg", 0, 0);
    tileSet[164] = new Tile("play/Library/LIBRARY46.jpg", 0, 0);
    tileSet[165] = new Tile("play/Library/LIBRARY47.jpg", 0, 0);
    tileSet[166] = new Tile("play/Library/LIBRARY48.jpg", 0, 0);
    
    tileSet[167] = new Tile("play/Tennis/Tennis1.png", 0, 0);

    tileSet[175] = new Tile("play/QinLake/QinLake1.jpg", 0, 0);
    tileSet[176] = new Tile("play/QinLake/QinLake2.jpg", 0, 0);
    tileSet[177] = new Tile("play/QinLake/QinLake3.jpg", 0, 0);
    tileSet[178] = new Tile("play/QinLake/QinLake4.jpg", 0, 0);
    tileSet[179] = new Tile("play/QinLake/QinLake5.jpg", 0, 0);
    tileSet[180] = new Tile("play/QinLake/QinLake6.jpg", 0, 0);
    tileSet[181] = new Tile("play/QinLake/QinLake7.jpg", 0, 0);
    tileSet[182] = new Tile("play/QinLake/QinLake8.jpg", 0, 0);
    tileSet[183] = new Tile("play/QinLake/QinLake9.jpg", 0, 0);
    tileSet[184] = new Tile("play/QinLake/QinLake10.jpg", 0, 0);
    tileSet[185] = new Tile("play/QinLake/QinLake11.jpg", 0, 0);
    tileSet[186] = new Tile("play/QinLake/QinLake12.jpg", 0, 0);
    tileSet[187] = new Tile("play/QinLake/QinLake13.jpg", 0, 0);
    tileSet[188] = new Tile("play/QinLake/QinLake14.jpg", 0, 0);
    tileSet[189] = new Tile("play/QinLake/QinLake15.jpg", 0, 0);
    tileSet[190] = new Tile("play/QinLake/QinLake16.jpg", 0, 0);
    tileSet[191] = new Tile("play/QinLake/QinLake17.jpg", 0, 0);
    tileSet[192] = new Tile("play/QinLake/QinLake18.jpg", 0, 0);
    tileSet[193] = new Tile("play/QinLake/QinLake19.jpg", 0, 0);
    tileSet[194] = new Tile("play/QinLake/QinLake20.jpg", 0, 0);
    tileSet[195] = new Tile("play/QinLake/QinLake21.jpg", 0, 0);
    tileSet[196] = new Tile("play/QinLake/QinLake22.jpg", 0, 0);
    tileSet[197] = new Tile("play/QinLake/QinLake23.jpg", 0, 0);
    tileSet[198] = new Tile("play/QinLake/QinLake24.jpg", 0, 0);
    tileSet[199] = new Tile("play/QinLake/QinLake25.jpg", 0, 0);
    tileSet[200] = new Tile("play/QinLake/QinLake26.jpg", 0, 0);
    tileSet[201] = new Tile("play/QinLake/QinLake27.jpg", 0, 0);
    tileSet[202] = new Tile("play/QinLake/QinLake28.jpg", 0, 0);
    tileSet[203] = new Tile("play/QinLake/QinLake29.jpg", 0, 0);
    tileSet[204] = new Tile("play/QinLake/QinLake30.jpg", 0, 0);
    tileSet[205] = new Tile("play/QinLake/QinLake31.jpg", 0, 0);
    tileSet[206] = new Tile("play/QinLake/QinLake32.jpg", 0, 0);
    tileSet[207] = new Tile("play/QinLake/QinLake33.jpg", 0, 0);
    tileSet[208] = new Tile("play/QinLake/QinLake34.jpg", 0, 0);
    tileSet[209] = new Tile("play/QinLake/QinLake35.jpg", 0, 0);
    tileSet[210] = new Tile("play/QinLake/QinLake36.jpg", 0, 0);
    tileSet[211] = new Tile("play/QinLake/QinLake37.jpg", 0, 0);
    tileSet[212] = new Tile("play/QinLake/QinLake38.jpg", 0, 0);
    tileSet[213] = new Tile("play/QinLake/QinLake39.jpg", 0, 0);
    tileSet[214] = new Tile("play/QinLake/QinLake40.jpg", 0, 0);

    
    tileSet[215] = new Tile("play/Tennis/Tennis2.png", 0, 0);
    tileSet[216] = new Tile("play/Tennis/Tennis3.png", 0, 0);
    tileSet[217] = new Tile("play/Tennis/Tennis4.png", 0, 0);
    tileSet[218] = new Tile("play/Tennis/Tennis5.png", 0, 0);
    tileSet[219] = new Tile("play/Tennis/Tennis6.png", 0, 0);
    tileSet[220] = new Tile("play/Tennis/Tennis7.png", 0, 0);
    tileSet[221] = new Tile("play/Tennis/Tennis8.png", 0, 0);
    tileSet[222] = new Tile("play/Tennis/Tennis9.png", 0, 0);
    tileSet[223] = new Tile("play/Tennis/Tennis10.png", 0, 0);
    tileSet[224] = new Tile("play/Tennis/Tennis11.png", 0, 0);
    tileSet[225] = new Tile("play/Tennis/Tennis12.png", 0, 0);
    tileSet[226] = new Tile("play/Tennis/Tennis13.png", 0, 0);
    tileSet[227] = new Tile("play/Tennis/Tennis14.png", 0, 0);
    tileSet[228] = new Tile("play/Tennis/Tennis15.png", 0, 0);
    tileSet[229] = new Tile("play/Tennis/Tennis16.png", 0, 0);
    tileSet[230] = new Tile("play/Tennis/Tennis17.png", 0, 0);
    tileSet[231] = new Tile("play/Tennis/Tennis18.png", 0, 0);
    tileSet[232] = new Tile("play/Tennis/Tennis19.png", 0, 0);
    tileSet[233] = new Tile("play/Tennis/Tennis20.png", 0, 0);
    tileSet[234] = new Tile("play/Tennis/Tennis21.png", 0, 0);
    tileSet[235] = new Tile("play/Tennis/Tennis22.png", 0, 0);
    tileSet[236] = new Tile("play/Tennis/Tennis23.png", 0, 0);
    tileSet[237] = new Tile("play/Tennis/Tennis24.png", 0, 0);
    tileSet[238] = new Tile("play/Tennis/Tennis25.png", 0, 0);
    tileSet[239] = new Tile("play/Tennis/Tennis26.png", 0, 0);
    tileSet[240] = new Tile("play/Tennis/Tennis27.png", 0, 0);
    tileSet[241] = new Tile("play/Tennis/Tennis28.png", 0, 0);
    tileSet[242] = new Tile("play/Tennis/Tennis29.png", 0, 0);
    tileSet[243] = new Tile("play/Tennis/Tennis30.png", 0, 0);
    tileSet[244] = new Tile("play/Tennis/Tennis31.png", 0, 0);
    tileSet[245] = new Tile("play/Tennis/Tennis32.png", 0, 0);
    tileSet[246] = new Tile("play/Tennis/Tennis33.png", 0, 0);
    tileSet[247] = new Tile("play/Tennis/Tennis34.png", 0, 0);
    tileSet[248] = new Tile("play/Tennis/Tennis35.png", 0, 0);
    tileSet[249] = new Tile("play/Tennis/Tennis36.png", 0, 0);
    tileSet[250] = new Tile("play/Tennis/Tennis37.png", 0, 0);
    tileSet[251] = new Tile("play/Tennis/Tennis38.png", 0, 0);
    tileSet[252] = new Tile("play/Tennis/Tennis39.png", 0, 0);
    tileSet[253] = new Tile("play/Tennis/Tennis40.png", 0, 0);
    tileSet[254] = new Tile("play/Tennis/Tennis41.png", 0, 0);
    tileSet[255] = new Tile("play/Tennis/Tennis42.png", 0, 0);

    tileSet[465] = new Tile("play/Code/Code1.jpg", 0, 0);
    tileSet[256] = new Tile("play/Code/Code2.jpg", 0, 0);
    tileSet[257] = new Tile("play/Code/Code3.jpg", 0, 0);
    tileSet[258] = new Tile("play/Code/Code4.jpg", 0, 0);
    tileSet[259] = new Tile("play/Code/Code5.jpg", 0, 0);
    tileSet[260] = new Tile("play/Code/Code6.jpg", 0, 0);
    tileSet[261] = new Tile("play/Code/Code7.jpg", 0, 0);
    tileSet[262] = new Tile("play/Code/Code8.jpg", 0, 0);
    tileSet[263] = new Tile("play/Code/Code9.jpg", 0, 0);
    tileSet[264] = new Tile("play/Code/Code10.jpg", 0, 0);
    tileSet[265] = new Tile("play/Code/Code11.jpg", 0, 0);
    tileSet[266] = new Tile("play/Code/Code12.jpg", 0, 0);
    tileSet[267] = new Tile("play/Code/Code13.jpg", 0, 0);
    tileSet[268] = new Tile("play/Code/Code14.jpg", 0, 0);
    tileSet[269] = new Tile("play/Code/Code15.jpg", 0, 0);
    tileSet[270] = new Tile("play/Code/Code16.jpg", 0, 0);
    tileSet[271] = new Tile("play/Code/Code17.jpg", 0, 0);
    tileSet[272] = new Tile("play/Code/Code18.jpg", 0, 0);
    tileSet[273] = new Tile("play/Code/Code19.jpg", 0, 0);
    tileSet[274] = new Tile("play/Code/Code20.jpg", 0, 0);
    tileSet[275] = new Tile("play/Code/Code21.jpg", 0, 0);
    tileSet[276] = new Tile("play/Code/Code22.jpg", 0, 0);
    tileSet[277] = new Tile("play/Code/Code23.jpg", 0, 0);
    tileSet[278] = new Tile("play/Code/Code24.jpg", 0, 0);
    tileSet[279] = new Tile("play/Code/Code25.jpg", 0, 0);
    tileSet[280] = new Tile("play/Code/Code26.jpg", 0, 0);
    tileSet[281] = new Tile("play/Code/Code27.jpg", 0, 0);
    tileSet[282] = new Tile("play/Code/Code28.jpg", 0, 0);
    tileSet[283] = new Tile("play/Code/Code29.jpg", 0, 0);
    tileSet[284] = new Tile("play/Code/Code30.jpg", 0, 0);

    tileSet[285] = new Tile("play/HAM/HAM1.png", 0, 0);
    tileSet[286] = new Tile("play/HAM/HAM2.png", 0, 0);
    tileSet[287] = new Tile("play/HAM/HAM3.png", 0, 0);
    tileSet[288] = new Tile("play/HAM/HAM4.png", 0, 0);
    tileSet[289] = new Tile("play/HAM/HAM5.png", 0, 0);
    tileSet[290] = new Tile("play/HAM/HAM6.png", 0, 0);
    tileSet[291] = new Tile("play/HAM/HAM7.png", 0, 0);
    tileSet[292] = new Tile("play/HAM/HAM8.png", 0, 0);
    tileSet[293] = new Tile("play/HAM/HAM9.png", 0, 0);
    tileSet[294] = new Tile("play/HAM/HAM10.png", 0, 0);
    tileSet[295] = new Tile("play/HAM/HAM11.png", 0, 0);
    tileSet[296] = new Tile("play/HAM/HAM12.png", 0, 0);
    tileSet[297] = new Tile("play/HAM/HAM13.png", 0, 0);
    tileSet[298] = new Tile("play/HAM/HAM14.png", 0, 0);
    tileSet[299] = new Tile("play/HAM/HAM15.png", 0, 0);
    tileSet[300] = new Tile("play/HAM/HAM16.png", 0, 0);
    tileSet[301] = new Tile("play/HAM/HAM17.png", 0, 0);
    tileSet[302] = new Tile("play/HAM/HAM18.png", 0, 0);
    tileSet[303] = new Tile("play/HAM/HAM19.png", 0, 0);
    tileSet[304] = new Tile("play/HAM/HAM20.png", 0, 0);
    tileSet[305] = new Tile("play/HAM/HAM21.png", 0, 0);
    tileSet[306] = new Tile("play/HAM/HAM22.png", 0, 0);
    tileSet[307] = new Tile("play/HAM/HAM23.png", 0, 0);
    tileSet[308] = new Tile("play/HAM/HAM24.png", 0, 0);
    tileSet[309] = new Tile("play/HAM/HAM25.png", 0, 0);
    tileSet[310] = new Tile("play/HAM/HAM26.png", 0, 0);
    tileSet[311] = new Tile("play/HAM/HAM27.png", 0, 0);
    tileSet[312] = new Tile("play/HAM/HAM28.png", 0, 0);
    tileSet[313] = new Tile("play/HAM/HAM29.png", 0, 0);
    tileSet[314] = new Tile("play/HAM/HAM30.png", 0, 0);
    tileSet[315] = new Tile("play/HAM/HAM31.png", 0, 0);
    tileSet[316] = new Tile("play/HAM/HAM32.png", 0, 0);
    tileSet[317] = new Tile("play/HAM/HAM33.png", 0, 0);
    tileSet[318] = new Tile("play/HAM/HAM34.png", 0, 0);
    tileSet[319] = new Tile("play/HAM/HAM35.png", 0, 0);
    tileSet[320] = new Tile("play/HAM/HAM36.png", 0, 0);

    tileSet[321] = new Tile("play/Pool/Pool1.png", 0, 0);
    tileSet[322] = new Tile("play/Pool/Pool2.png", 0, 0);
    tileSet[323] = new Tile("play/Pool/Pool3.png", 0, 0);
    tileSet[324] = new Tile("play/Pool/Pool4.png", 0, 0);
    tileSet[325] = new Tile("play/Pool/Pool5.png", 0, 0);
    tileSet[326] = new Tile("play/Pool/Pool6.png", 0, 0);
    tileSet[327] = new Tile("play/Pool/Pool7.png", 0, 0);
    tileSet[328] = new Tile("play/Pool/Pool8.png", 0, 0);
    tileSet[329] = new Tile("play/Pool/Pool9.png", 0, 0);
    tileSet[330] = new Tile("play/Pool/Pool10.png", 0, 0);
    tileSet[331] = new Tile("play/Pool/Pool11.png", 0, 0);
    tileSet[332] = new Tile("play/Pool/Pool12.png", 0, 0);
    tileSet[333] = new Tile("play/Pool/Pool13.png", 0, 0);
    tileSet[334] = new Tile("play/Pool/Pool14.png", 0, 0);
    tileSet[335] = new Tile("play/Pool/Pool15.png", 0, 0);
    tileSet[336] = new Tile("play/Pool/Pool16.png", 0, 0);
    tileSet[337] = new Tile("play/Pool/Pool17.png", 0, 0);
    tileSet[338] = new Tile("play/Pool/Pool18.png", 0, 0);
    tileSet[339] = new Tile("play/Pool/Pool19.png", 0, 0);
    tileSet[340] = new Tile("play/Pool/Pool20.png", 0, 0);
    tileSet[341] = new Tile("play/Pool/Pool21.png", 0, 0);
    tileSet[342] = new Tile("play/Pool/Pool22.png", 0, 0);
    tileSet[343] = new Tile("play/Pool/Pool23.png", 0, 0);
    tileSet[344] = new Tile("play/Pool/Pool24.png", 0, 0);
    tileSet[345] = new Tile("play/Pool/Pool25.png", 0, 0);

    tileSet[346] = new Tile("play/Parking/Parking1.png", 0, 0);
    tileSet[347] = new Tile("play/Parking/Parking2.png", 0, 0);
    tileSet[348] = new Tile("play/Parking/Parking3.png", 0, 0);
    tileSet[349] = new Tile("play/Parking/Parking4.png", 0, 0);
    tileSet[350] = new Tile("play/Parking/Parking5.png", 0, 0);
    tileSet[351] = new Tile("play/Parking/Parking6.png", 0, 0);
    tileSet[352] = new Tile("play/Parking/Parking7.png", 0, 0);
    tileSet[353] = new Tile("play/Parking/Parking8.png", 0, 0);
    tileSet[354] = new Tile("play/Parking/Parking9.png", 0, 0);
    tileSet[355] = new Tile("play/Parking/Parking10.png", 0, 0);
    tileSet[356] = new Tile("play/Parking/Parking11.png", 0, 0);
    tileSet[357] = new Tile("play/Parking/Parking12.png", 0, 0);
    tileSet[358] = new Tile("play/Parking/Parking13.png", 0, 0);
    tileSet[359] = new Tile("play/Parking/Parking14.png", 0, 0);
    tileSet[360] = new Tile("play/Parking/Parking15.png", 0, 0);
    tileSet[361] = new Tile("play/Parking/Parking16.png", 0, 0);
    tileSet[362] = new Tile("play/Parking/Parking17.png", 0, 0);
    tileSet[363] = new Tile("play/Parking/Parking18.png", 0, 0);

    tileSet[364] = new Tile("play/Club/Club1.jpg", 0, 0);
    tileSet[365] = new Tile("play/Club/Club2.jpg", 0, 0);
    tileSet[366] = new Tile("play/Club/Club3.jpg", 0, 0);
    tileSet[367] = new Tile("play/Club/Club4.jpg", 0, 0);
    tileSet[368] = new Tile("play/Club/Club5.jpg", 0, 0);
    tileSet[369] = new Tile("play/Club/Club6.jpg", 0, 0);
    tileSet[370] = new Tile("play/Club/Club7.jpg", 0, 0);
    tileSet[371] = new Tile("play/Club/Club8.jpg", 0, 0);
    tileSet[372] = new Tile("play/Club/Club9.jpg", 0, 0);
    tileSet[373] = new Tile("play/Club/Club10.jpg", 0, 0);
    tileSet[374] = new Tile("play/Club/Club11.jpg", 0, 0);
    tileSet[375] = new Tile("play/Club/Club12.jpg", 0, 0);
    tileSet[376] = new Tile("play/Club/Club13.jpg", 0, 0);
    tileSet[377] = new Tile("play/Club/Club14.jpg", 0, 0);
    tileSet[378] = new Tile("play/Club/Club15.jpg", 0, 0);
    tileSet[379] = new Tile("play/Club/Club16.jpg", 0, 0);
    tileSet[380] = new Tile("play/Club/Club17.jpg", 0, 0);
    tileSet[381] = new Tile("play/Club/Club18.jpg", 0, 0);
    tileSet[382] = new Tile("play/Club/Club19.jpg", 0, 0);
    tileSet[383] = new Tile("play/Club/Club20.jpg", 0, 0);
    tileSet[384] = new Tile("play/Club/Club21.jpg", 0, 0);
    tileSet[385] = new Tile("play/Club/Club22.jpg", 0, 0);
    tileSet[386] = new Tile("play/Club/Club23.jpg", 0, 0);
    tileSet[387] = new Tile("play/Club/Club24.jpg", 0, 0);
    tileSet[388] = new Tile("play/Club/Club25.jpg", 0, 0);
    tileSet[389] = new Tile("play/Club/Club26.jpg", 0, 0);
    tileSet[390] = new Tile("play/Club/Club27.jpg", 0, 0);
    tileSet[391] = new Tile("play/Club/Club28.jpg", 0, 0);
    tileSet[392] = new Tile("play/Club/Club29.jpg", 0, 0);
    tileSet[393] = new Tile("play/Club/Club30.jpg", 0, 0);
    tileSet[394] = new Tile("play/Club/Club31.jpg", 0, 0);
    tileSet[395] = new Tile("play/Club/Club32.jpg", 0, 0);

    tileSet[396] = new Tile("play/Shop/Shop1.png", 0, 0);
    tileSet[397] = new Tile("play/Shop/Shop2.png", 0, 0);
    tileSet[398] = new Tile("play/Shop/Shop3.png", 0, 0);
    tileSet[399] = new Tile("play/Shop/Shop4.png", 0, 0);
    tileSet[400] = new Tile("play/Shop/Shop5.png", 0, 0);
    tileSet[401] = new Tile("play/Shop/Shop6.png", 0, 0);
    tileSet[402] = new Tile("play/Shop/Shop7.png", 0, 0);
    tileSet[403] = new Tile("play/Shop/Shop8.png", 0, 0);
    tileSet[404] = new Tile("play/Shop/Shop9.png", 0, 0);

    tileSet[405] = new Tile("play/rest/rest1.png", 0, 0);
    tileSet[406] = new Tile("play/rest/rest2.png", 0, 0);
    tileSet[407] = new Tile("play/rest/rest3.png", 0, 0);
    tileSet[408] = new Tile("play/rest/rest4.png", 0, 0);
    tileSet[409] = new Tile("play/rest/rest5.png", 0, 0);
    tileSet[410] = new Tile("play/rest/rest6.png", 0, 0);
    tileSet[411] = new Tile("play/rest/rest7.png", 0, 0);
    tileSet[412] = new Tile("play/rest/rest8.png", 0, 0);
    tileSet[413] = new Tile("play/rest/rest9.png", 0, 0);
    tileSet[414] = new Tile("play/rest/rest10.png", 0, 0);
    tileSet[415] = new Tile("play/rest/rest11.png", 0, 0);
    tileSet[416] = new Tile("play/rest/rest12.png", 0, 0);

    tileSet[417] = new Tile("play/Castle/Castle1.png", 0, 0);
    tileSet[418] = new Tile("play/Castle/Castle2.png", 0, 0);
    tileSet[419] = new Tile("play/Castle/Castle3.png", 0, 0);
    tileSet[420] = new Tile("play/Castle/Castle4.png", 0, 0);
    tileSet[421] = new Tile("play/Castle/Castle5.png", 0, 0);
    tileSet[422] = new Tile("play/Castle/Castle6.png", 0, 0);
    tileSet[423] = new Tile("play/Castle/Castle7.png", 0, 0);
    tileSet[424] = new Tile("play/Castle/Castle8.png", 0, 0);
    tileSet[425] = new Tile("play/Castle/Castle9.png", 0, 0);
    tileSet[426] = new Tile("play/Castle/Castle10.png", 0, 0);
    tileSet[427] = new Tile("play/Castle/Castle11.png", 0, 0);
    tileSet[428] = new Tile("play/Castle/Castle12.png", 0, 0);
    tileSet[429] = new Tile("play/Castle/Castle13.png", 0, 0);
    tileSet[430] = new Tile("play/Castle/Castle14.png", 0, 0);
    tileSet[431] = new Tile("play/Castle/Castle15.png", 0, 0);
    tileSet[432] = new Tile("play/Castle/Castle16.png", 0, 0);
    tileSet[433] = new Tile("play/Castle/Castle17.png", 0, 0);
    tileSet[434] = new Tile("play/Castle/Castle18.png", 0, 0);
    tileSet[435] = new Tile("play/Castle/Castle19.png", 0, 0);
    tileSet[436] = new Tile("play/Castle/Castle20.png", 0, 0);
    tileSet[437] = new Tile("play/Castle/Castle21.png", 0, 0);
    tileSet[438] = new Tile("play/Castle/Castle22.png", 0, 0);
    tileSet[439] = new Tile("play/Castle/Castle23.png", 0, 0);
    tileSet[440] = new Tile("play/Castle/Castle24.png", 0, 0);
    tileSet[441] = new Tile("play/Castle/Castle25.png", 0, 0);
    tileSet[442] = new Tile("play/Castle/Castle26.png", 0, 0);
    tileSet[443] = new Tile("play/Castle/Castle27.png", 0, 0);
    tileSet[444] = new Tile("play/Castle/Castle28.png", 0, 0);
    tileSet[445] = new Tile("play/Castle/Castle29.png", 0, 0);
    tileSet[446] = new Tile("play/Castle/Castle30.png", 0, 0);
    tileSet[447] = new Tile("play/Castle/Castle31.png", 0, 0);
    tileSet[448] = new Tile("play/Castle/Castle32.png", 0, 0);
    tileSet[449] = new Tile("play/Castle/Castle33.png", 0, 0);
    tileSet[450] = new Tile("play/Castle/Castle34.png", 0, 0);
    tileSet[451] = new Tile("play/Castle/Castle35.png", 0, 0);
    tileSet[452] = new Tile("play/Castle/Castle36.png", 0, 0);
    tileSet[453] = new Tile("play/Castle/Castle37.png", 0, 0);
    tileSet[454] = new Tile("play/Castle/Castle38.png", 0, 0);
    tileSet[455] = new Tile("play/Castle/Castle39.png", 0, 0);
    tileSet[456] = new Tile("play/Castle/Castle40.png", 0, 0);
    tileSet[457] = new Tile("play/Castle/Castle41.png", 0, 0);
    tileSet[458] = new Tile("play/Castle/Castle42.png", 0, 0);
    tileSet[459] = new Tile("play/Castle/Castle43.png", 0, 0);
    tileSet[460] = new Tile("play/Castle/Castle44.png", 0, 0);
    tileSet[461] = new Tile("play/Castle/Castle45.png", 0, 0);
    tileSet[462] = new Tile("play/Castle/Castle46.png", 0, 0);
    tileSet[463] = new Tile("play/Castle/Castle47.png", 0, 0);
    tileSet[464] = new Tile("play/Castle/Castle48.png", 0, 0);

    tileSet[466] = new Tile("play/Coffee/Coffee1.png", 0, 0);
    tileSet[467] = new Tile("play/Coffee/Coffee2.png", 0, 0);
    tileSet[468] = new Tile("play/Coffee/Coffee3.png", 0, 0);
    tileSet[469] = new Tile("play/Coffee/Coffee4.png", 0, 0);
    tileSet[470] = new Tile("play/Coffee/Coffee5.png", 0, 0);
    tileSet[471] = new Tile("play/Coffee/Coffee6.png", 0, 0);
    tileSet[472] = new Tile("play/Coffee/Coffee7.png", 0, 0);
    tileSet[473] = new Tile("play/Coffee/Coffee8.png", 0, 0);
    tileSet[474] = new Tile("play/Coffee/Coffee9.png", 0, 0);
    tileSet[475] = new Tile("play/Coffee/Coffee10.png", 0, 0);
    tileSet[476] = new Tile("play/Coffee/Coffee11.png", 0, 0);
    tileSet[477] = new Tile("play/Coffee/Coffee12.png", 0, 0);
    tileSet[478] = new Tile("play/Coffee/Coffee13.png", 0, 0);
    tileSet[479] = new Tile("play/Coffee/Coffee14.png", 0, 0);
    tileSet[480] = new Tile("play/Coffee/Coffee15.png", 0, 0);
    tileSet[481] = new Tile("play/Coffee/Coffee16.png", 0, 0);
    tileSet[482] = new Tile("play/Coffee/Coffee17.png", 0, 0);
    tileSet[483] = new Tile("play/Coffee/Coffee18.png", 0, 0);
    tileSet[484] = new Tile("play/Coffee/Coffee19.png", 0, 0);
    tileSet[485] = new Tile("play/Coffee/Coffee20.png", 0, 0);
    tileSet[486] = new Tile("play/Coffee/Coffee21.png", 0, 0);
    tileSet[487] = new Tile("play/Coffee/Coffee22.png", 0, 0);
    tileSet[488] = new Tile("play/Coffee/Coffee23.png", 0, 0);
    tileSet[489] = new Tile("play/Coffee/Coffee24.png", 0, 0);

    tileSet[490] = new Tile("play/grass/GRASS1.jpg", 0, 0);
    tileSet[491] = new Tile("play/grass/GRASS2.jpg", 0, 0);
    tileSet[492] = new Tile("play/grass/GRASS3.jpg", 0, 0);
    tileSet[493] = new Tile("play/grass/GRASS4.jpg", 0, 0);
    tileSet[494] = new Tile("play/grass/GRASS5.jpg", 0, 0);
    tileSet[495] = new Tile("play/grass/GRASS6.jpg", 0, 0);
    tileSet[496] = new Tile("play/grass/GRASS7.jpg", 0, 0);
    tileSet[497] = new Tile("play/grass/GRASS8.jpg", 0, 0);
    tileSet[498] = new Tile("play/grass/GRASS9.jpg", 0, 0);
    tileSet[499] = new Tile("play/grass/GRASS10.jpg", 0, 0);
    tileSet[500] = new Tile("play/grass/GRASS11.jpg", 0, 0);
    tileSet[501] = new Tile("play/grass/GRASS12.jpg", 0, 0);
    tileSet[502] = new Tile("play/grass/GRASS13.jpg", 0, 0);
    tileSet[503] = new Tile("play/grass/GRASS14.jpg", 0, 0);
    tileSet[504] = new Tile("play/grass/GRASS15.jpg", 0, 0);
    tileSet[505] = new Tile("play/grass/GRASS16.jpg", 0, 0);
    tileSet[506] = new Tile("play/grass/GRASS17.jpg", 0, 0);
    tileSet[507] = new Tile("play/grass/GRASS18.jpg", 0, 0);
    tileSet[508] = new Tile("play/grass/GRASS19.jpg", 0, 0);
    tileSet[509] = new Tile("play/grass/GRASS20.jpg", 0, 0);
    tileSet[510] = new Tile("play/grass/GRASS21.jpg", 0, 0);
    tileSet[511] = new Tile("play/grass/GRASS22.jpg", 0, 0);
    tileSet[512] = new Tile("play/grass/GRASS23.jpg", 0, 0);
    tileSet[513] = new Tile("play/grass/GRASS24.jpg", 0, 0);

}

/*Map::~Map() {
    tileSet.clear();
}*/

void Map::cleanup() {
    if (tileset) al_destroy_bitmap(tileset);
    //if (coinSprites) al_destroy_bitmap(coinSprites);
    //if (coinAudio) al_destroy_sample(coinAudio);
}

void Map::Initialize() {
    //tiles = std::vector<std::vector<int>>(PlayScene::MapHeight, std::vector<int>(PlayScene::MapWidth, static_cast<int>(BlockType::FLOOR)));
    tiles = std::vector<std::vector<BlockType>>(PlayScene::MapHeight, std::vector<BlockType>(PlayScene::MapWidth, BlockType::FLOOR));
}

void Map::Terminate() {
    IScene::Terminate();
}

void Map::loadMapFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to open map file: " << filepath << std::endl;
        return;
    }

    // 簡單示範從檔案讀地圖
    file >> rows >> cols;
    if (!file || rows <= 0 || cols <= 0) {
        std::cerr << "Invalid map dimensions in file." << std::endl;
        return;
    }

    mapGrid.resize(rows, std::vector<BlockType>(cols, BlockType::NOTHING));
    //mapGrid.resize(rows, std::vector<BlockType>(cols));
    //coinStatus.resize(rows, std::vector<CoinStatus>(cols, CoinStatus::DISAPPEAR));
    //coinAnimationFrame.resize(rows, std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r) {
        for (int c =0 ; c < cols; ++c) {
            //char tile;
            int tile;
            file >> tile;
            //mapGrid[r][c] = static_cast<BlockType>(tile-'0');
            //if (mapGrid[r][c] == BlockType::COIN) {
            //    coinStatus[r][c] = CoinStatus::APPEAR;
            //}
            if (!file) {
                std::cerr << "Error reading tile at (" << r << "," << c << ")." << std::endl;
                throw std::ios_base::failure("Map data is corrupted.");
            }

            //std::ifstream file("map1.txt");
            //int count = 0;
            //int tile;
            //while (file >> tile) ++count;
            //std::cout << "Total tile count: " << count << std::endl;


           switch (tile) {
                case 0: mapGrid[r][c] = BlockType::FLOOR; break;
                case 1: mapGrid[r][c] = BlockType::WALL; break;
                case 2: mapGrid[r][c] = BlockType::TREE1; break;
                case 3: mapGrid[r][c] = BlockType::GROUND1; break;
                case 4: mapGrid[r][c] = BlockType::GROUND2; break;
                case 5: mapGrid[r][c] = BlockType::GROUND3; break;
                case 6: mapGrid[r][c] = BlockType::GROUND4; break;
                case 7: mapGrid[r][c] = BlockType::GROUND5; break;
                case 8: mapGrid[r][c] = BlockType::GROUND6; break;
                case 9: mapGrid[r][c] = BlockType::GROUND7; break;
                case 10: mapGrid[r][c] = BlockType::GROUND8; break;
                case 11: mapGrid[r][c] = BlockType::GROUND9; break;
                case 12: mapGrid[r][c] = BlockType::GROUND10; break;
                case 13: mapGrid[r][c] = BlockType::GROUND11; break;
                case 14: mapGrid[r][c] = BlockType::GROUND12; break;
                case 15: mapGrid[r][c] = BlockType::GROUND13; break;
                case 16: mapGrid[r][c] = BlockType::GROUND14; break;
                case 17: mapGrid[r][c] = BlockType::GROUND15; break;
                case 18: mapGrid[r][c] = BlockType::GROUND16; break;
                case 19: mapGrid[r][c] = BlockType::GROUND17; break;
                case 20: mapGrid[r][c] = BlockType::GROUND18; break;
                case 21: mapGrid[r][c] = BlockType::GROUND19; break;
                case 22: mapGrid[r][c] = BlockType::GROUND20; break;
                case 23: mapGrid[r][c] = BlockType::GROUND21; break;
                case 24: mapGrid[r][c] = BlockType::GROUND22; break;
                case 25: mapGrid[r][c] = BlockType::GROUND23; break;
                case 26: mapGrid[r][c] = BlockType::GROUND24; break;
                case 27: mapGrid[r][c] = BlockType::GROUND25; break;
                case 28: mapGrid[r][c] = BlockType::GROUND26; break;
                case 29: mapGrid[r][c] = BlockType::GROUND27; break;
                case 30: mapGrid[r][c] = BlockType::GROUND28; break;
                case 31: mapGrid[r][c] = BlockType::GROUND29; break;
                case 32: mapGrid[r][c] = BlockType::GROUND30; break;
                case 33: mapGrid[r][c] = BlockType::GROUND31; break;
                case 34: mapGrid[r][c] = BlockType::GROUND32; break;
                case 35: mapGrid[r][c] = BlockType::GROUND33; break;
                case 36: mapGrid[r][c] = BlockType::GROUND34; break;
                case 37: mapGrid[r][c] = BlockType::GROUND35; break;
                case 168: mapGrid[r][c] = BlockType::GROUND36; break;
                case 169: mapGrid[r][c] = BlockType::GROUND37; break;
                case 170: mapGrid[r][c] = BlockType::GROUND38; break;
                case 171: mapGrid[r][c] = BlockType::GROUND39; break;
                case 172: mapGrid[r][c] = BlockType::GROUND40; break;
                case 173: mapGrid[r][c] = BlockType::GROUND41; break;
                case 174: mapGrid[r][c] = BlockType::GROUND42; break;

                case 38: mapGrid[r][c] = BlockType::CSBUILDING1; break;
                case 39: mapGrid[r][c] = BlockType::CSBUILDING2; break;
                case 40: mapGrid[r][c] = BlockType::CSBUILDING3; break;
                case 41: mapGrid[r][c] = BlockType::CSBUILDING4; break;
                case 42: mapGrid[r][c] = BlockType::CSBUILDING5; break;
                case 43: mapGrid[r][c] = BlockType::CSBUILDING6; break;
                case 44: mapGrid[r][c] = BlockType::CSBUILDING7; break;
                case 45: mapGrid[r][c] = BlockType::CSBUILDING8; break;
                case 46: mapGrid[r][c] = BlockType::CSBUILDING9; break;
                case 47: mapGrid[r][c] = BlockType::CSBUILDING10; break;
                case 48: mapGrid[r][c] = BlockType::CSBUILDING11; break;
                case 49: mapGrid[r][c] = BlockType::CSBUILDING12; break;
                case 50: mapGrid[r][c] = BlockType::CSBUILDING13; break;
                case 51: mapGrid[r][c] = BlockType::CSBUILDING14; break;
                case 52: mapGrid[r][c] = BlockType::CSBUILDING15; break;
                case 53: mapGrid[r][c] = BlockType::CSBUILDING16; break;
                case 54: mapGrid[r][c] = BlockType::CSBUILDING17; break;
                case 55: mapGrid[r][c] = BlockType::CSBUILDING18; break;
                case 56: mapGrid[r][c] = BlockType::CSBUILDING19; break;
                case 57: mapGrid[r][c] = BlockType::CSBUILDING20; break;
                case 58: mapGrid[r][c] = BlockType::CSBUILDING21; break;
                case 59: mapGrid[r][c] = BlockType::CSBUILDING22; break;
                case 60: mapGrid[r][c] = BlockType::CSBUILDING23; break;
                case 61: mapGrid[r][c] = BlockType::CSBUILDING24; break;
                case 62: mapGrid[r][c] = BlockType::CSBUILDING25; break;
                case 63: mapGrid[r][c] = BlockType::CSBUILDING26; break;
                case 64: mapGrid[r][c] = BlockType::CSBUILDING27; break;
                case 65: mapGrid[r][c] = BlockType::CSBUILDING28; break;
                case 66: mapGrid[r][c] = BlockType::CSBUILDING29; break;
                case 67: mapGrid[r][c] = BlockType::CSBUILDING30; break;
                case 68: mapGrid[r][c] = BlockType::CSBUILDING31; break;
                case 69: mapGrid[r][c] = BlockType::CSBUILDING32; break;
                case 70: mapGrid[r][c] = BlockType::CSBUILDING33; break;
                case 71: mapGrid[r][c] = BlockType::CSBUILDING34; break;
                case 72: mapGrid[r][c] = BlockType::CSBUILDING35; break;
                case 73: mapGrid[r][c] = BlockType::CSBUILDING36; break;
                case 74: mapGrid[r][c] = BlockType::CSBUILDING37; break;
                case 75: mapGrid[r][c] = BlockType::CSBUILDING38; break;
                case 76: mapGrid[r][c] = BlockType::CSBUILDING39; break;
                case 77: mapGrid[r][c] = BlockType::CSBUILDING40; break;
                case 78: mapGrid[r][c] = BlockType::CSBUILDING41; break;
                case 79: mapGrid[r][c] = BlockType::CSBUILDING42; break;
                case 80: mapGrid[r][c] = BlockType::CSBUILDING43; break;
                case 81: mapGrid[r][c] = BlockType::CSBUILDING44; break;
                case 82: mapGrid[r][c] = BlockType::CSBUILDING45; break;
                case 83: mapGrid[r][c] = BlockType::CSBUILDING46; break;
                case 84: mapGrid[r][c] = BlockType::CSBUILDING47; break;
                case 85: mapGrid[r][c] = BlockType::CSBUILDING48; break;
                case 86: mapGrid[r][c] = BlockType::CSBUILDING49; break;
                case 87: mapGrid[r][c] = BlockType::CSBUILDING50; break;

                case 89: mapGrid[r][c] = BlockType::LAKE1; break;
                case 90: mapGrid[r][c] = BlockType::LAKE2; break;
                case 91: mapGrid[r][c] = BlockType::LAKE3; break;
                case 92: mapGrid[r][c] = BlockType::LAKE4; break;
                case 93: mapGrid[r][c] = BlockType::LAKE5; break;
                case 94: mapGrid[r][c] = BlockType::LAKE6; break;
                case 95: mapGrid[r][c] = BlockType::LAKE7; break;
                case 96: mapGrid[r][c] = BlockType::LAKE8; break;
                case 97: mapGrid[r][c] = BlockType::LAKE9; break;
                case 98: mapGrid[r][c] = BlockType::LAKE10; break;
                case 99: mapGrid[r][c] = BlockType::LAKE11; break;
                case 100: mapGrid[r][c] = BlockType::LAKE12; break;
                case 101: mapGrid[r][c] = BlockType::LAKE13; break;
                case 102: mapGrid[r][c] = BlockType::LAKE14; break;
                case 103: mapGrid[r][c] = BlockType::LAKE15; break;
                case 104: mapGrid[r][c] = BlockType::LAKE16; break;
                case 105: mapGrid[r][c] = BlockType::LAKE17; break;
                case 106: mapGrid[r][c] = BlockType::LAKE18; break;
                case 107: mapGrid[r][c] = BlockType::LAKE19; break;
                case 108: mapGrid[r][c] = BlockType::LAKE20; break;
                case 109: mapGrid[r][c] = BlockType::LAKE21; break;
                case 110: mapGrid[r][c] = BlockType::LAKE22; break;
                case 111: mapGrid[r][c] = BlockType::LAKE23; break;
                case 112: mapGrid[r][c] = BlockType::LAKE24; break;
                case 113: mapGrid[r][c] = BlockType::LAKE25; break;

                /*case 113: mapGrid[r][c] = BlockType::LAKE26; break;
                case 114: mapGrid[r][c] = BlockType::LAKE27; break;
                case 115: mapGrid[r][c] = BlockType::LAKE28; break;
                case 116: mapGrid[r][c] = BlockType::LAKE29; break;
                case 117: mapGrid[r][c] = BlockType::LAKE30; break;
                case 118: mapGrid[r][c] = BlockType::LAKE31; break;*/
                case 119: mapGrid[r][c] = BlockType::LIBRARY1; break;
                case 120: mapGrid[r][c] = BlockType::LIBRARY2; break;
                case 121: mapGrid[r][c] = BlockType::LIBRARY3; break;
                case 122: mapGrid[r][c] = BlockType::LIBRARY4; break;
                case 123: mapGrid[r][c] = BlockType::LIBRARY5; break;
                case 124: mapGrid[r][c] = BlockType::LIBRARY6; break;
                case 125: mapGrid[r][c] = BlockType::LIBRARY7; break;
                case 126: mapGrid[r][c] = BlockType::LIBRARY8; break;
                case 127: mapGrid[r][c] = BlockType::LIBRARY9; break;
                case 128: mapGrid[r][c] = BlockType::LIBRARY10; break;
                case 129: mapGrid[r][c] = BlockType::LIBRARY11; break;
                case 130: mapGrid[r][c] = BlockType::LIBRARY12; break;
                case 131: mapGrid[r][c] = BlockType::LIBRARY13; break;
                case 132: mapGrid[r][c] = BlockType::LIBRARY14; break;
                case 133: mapGrid[r][c] = BlockType::LIBRARY15; break;
                case 134: mapGrid[r][c] = BlockType::LIBRARY16; break;
                case 135: mapGrid[r][c] = BlockType::LIBRARY17; break;
                case 136: mapGrid[r][c] = BlockType::LIBRARY18; break;
                case 137: mapGrid[r][c] = BlockType::LIBRARY19; break;
                case 138: mapGrid[r][c] = BlockType::LIBRARY20; break;
                case 139: mapGrid[r][c] = BlockType::LIBRARY21; break;
                case 140: mapGrid[r][c] = BlockType::LIBRARY22; break;
                case 141: mapGrid[r][c] = BlockType::LIBRARY23; break;
                case 142: mapGrid[r][c] = BlockType::LIBRARY24; break;
                case 143: mapGrid[r][c] = BlockType::LIBRARY25; break;
                case 144: mapGrid[r][c] = BlockType::LIBRARY26; break;
                case 145: mapGrid[r][c] = BlockType::LIBRARY27; break;
                case 146: mapGrid[r][c] = BlockType::LIBRARY28; break;
                case 147: mapGrid[r][c] = BlockType::LIBRARY29; break;
                case 148: mapGrid[r][c] = BlockType::LIBRARY30; break;
                case 149: mapGrid[r][c] = BlockType::LIBRARY31; break;
                case 150: mapGrid[r][c] = BlockType::LIBRARY32; break;
                case 151: mapGrid[r][c] = BlockType::LIBRARY33; break;
                case 152: mapGrid[r][c] = BlockType::LIBRARY34; break;
                case 153: mapGrid[r][c] = BlockType::LIBRARY35; break;
                case 154: mapGrid[r][c] = BlockType::LIBRARY36; break;
                case 155: mapGrid[r][c] = BlockType::LIBRARY37; break;
                case 156: mapGrid[r][c] = BlockType::LIBRARY38; break;
                case 157: mapGrid[r][c] = BlockType::LIBRARY39; break;
                case 158: mapGrid[r][c] = BlockType::LIBRARY40; break;
                case 159: mapGrid[r][c] = BlockType::LIBRARY41; break;
                case 160: mapGrid[r][c] = BlockType::LIBRARY42; break;
                case 161: mapGrid[r][c] = BlockType::LIBRARY43; break;
                case 162: mapGrid[r][c] = BlockType::LIBRARY44; break;
                case 163: mapGrid[r][c] = BlockType::LIBRARY45; break;
                case 164: mapGrid[r][c] = BlockType::LIBRARY46; break;
                case 165: mapGrid[r][c] = BlockType::LIBRARY47; break;
                case 166: mapGrid[r][c] = BlockType::LIBRARY48; break;

                case 167: mapGrid[r][c] = BlockType::TENNIS1; break;

                case 175: mapGrid[r][c] = BlockType::QINLAKE1; break;
                case 176: mapGrid[r][c] = BlockType::QINLAKE2; break;
                case 177: mapGrid[r][c] = BlockType::QINLAKE3; break;
                case 178: mapGrid[r][c] = BlockType::QINLAKE4; break;
                case 179: mapGrid[r][c] = BlockType::QINLAKE5; break;
                case 180: mapGrid[r][c] = BlockType::QINLAKE6; break;
                case 181: mapGrid[r][c] = BlockType::QINLAKE7; break;
                case 182: mapGrid[r][c] = BlockType::QINLAKE8; break;
                case 183: mapGrid[r][c] = BlockType::QINLAKE9; break;
                case 184: mapGrid[r][c] = BlockType::QINLAKE10; break;
                case 185: mapGrid[r][c] = BlockType::QINLAKE11; break;
                case 186: mapGrid[r][c] = BlockType::QINLAKE12; break;
                case 187: mapGrid[r][c] = BlockType::QINLAKE13; break;
                case 188: mapGrid[r][c] = BlockType::QINLAKE14; break;
                case 189: mapGrid[r][c] = BlockType::QINLAKE15; break;
                case 190: mapGrid[r][c] = BlockType::QINLAKE16; break;
                case 191: mapGrid[r][c] = BlockType::QINLAKE17; break;
                case 192: mapGrid[r][c] = BlockType::QINLAKE18; break;
                case 193: mapGrid[r][c] = BlockType::QINLAKE19; break;
                case 194: mapGrid[r][c] = BlockType::QINLAKE20; break;
                case 195: mapGrid[r][c] = BlockType::QINLAKE21; break;
                case 196: mapGrid[r][c] = BlockType::QINLAKE22; break;
                case 197: mapGrid[r][c] = BlockType::QINLAKE23; break;
                case 198: mapGrid[r][c] = BlockType::QINLAKE24; break;
                case 199: mapGrid[r][c] = BlockType::QINLAKE25; break;
                case 200: mapGrid[r][c] = BlockType::QINLAKE26; break;
                case 201: mapGrid[r][c] = BlockType::QINLAKE27; break;
                case 202: mapGrid[r][c] = BlockType::QINLAKE28; break;
                case 203: mapGrid[r][c] = BlockType::QINLAKE29; break;
                case 204: mapGrid[r][c] = BlockType::QINLAKE30; break;
                case 205: mapGrid[r][c] = BlockType::QINLAKE31; break;
                case 206: mapGrid[r][c] = BlockType::QINLAKE32; break;
                case 207: mapGrid[r][c] = BlockType::QINLAKE33; break;
                case 208: mapGrid[r][c] = BlockType::QINLAKE34; break;
                case 209: mapGrid[r][c] = BlockType::QINLAKE35; break;
                case 210: mapGrid[r][c] = BlockType::QINLAKE36; break;
                case 211: mapGrid[r][c] = BlockType::QINLAKE37; break;
                case 212: mapGrid[r][c] = BlockType::QINLAKE38; break;
                case 213: mapGrid[r][c] = BlockType::QINLAKE39; break;
                case 214: mapGrid[r][c] = BlockType::QINLAKE40; break;

                case 215: mapGrid[r][c] = BlockType::TENNIS2; break;
                case 216: mapGrid[r][c] = BlockType::TENNIS3; break;
                case 217: mapGrid[r][c] = BlockType::TENNIS4; break;
                case 218: mapGrid[r][c] = BlockType::TENNIS5; break;
                case 219: mapGrid[r][c] = BlockType::TENNIS6; break;
                case 220: mapGrid[r][c] = BlockType::TENNIS7; break;
                case 221: mapGrid[r][c] = BlockType::TENNIS8; break;
                case 222: mapGrid[r][c] = BlockType::TENNIS9; break;
                case 223: mapGrid[r][c] = BlockType::TENNIS10; break;
                case 224: mapGrid[r][c] = BlockType::TENNIS11; break;
                case 225: mapGrid[r][c] = BlockType::TENNIS12; break;
                case 226: mapGrid[r][c] = BlockType::TENNIS13; break;
                case 227: mapGrid[r][c] = BlockType::TENNIS14; break;
                case 228: mapGrid[r][c] = BlockType::TENNIS15; break;
                case 229: mapGrid[r][c] = BlockType::TENNIS16; break;
                case 230: mapGrid[r][c] = BlockType::TENNIS17; break;
                case 231: mapGrid[r][c] = BlockType::TENNIS18; break;
                case 232: mapGrid[r][c] = BlockType::TENNIS19; break;
                case 233: mapGrid[r][c] = BlockType::TENNIS20; break;
                case 234: mapGrid[r][c] = BlockType::TENNIS21; break;
                case 235: mapGrid[r][c] = BlockType::TENNIS22; break;
                case 236: mapGrid[r][c] = BlockType::TENNIS23; break;
                case 237: mapGrid[r][c] = BlockType::TENNIS24; break;
                case 238: mapGrid[r][c] = BlockType::TENNIS25; break;
                case 239: mapGrid[r][c] = BlockType::TENNIS26; break;
                case 240: mapGrid[r][c] = BlockType::TENNIS27; break;
                case 241: mapGrid[r][c] = BlockType::TENNIS28; break;
                case 242: mapGrid[r][c] = BlockType::TENNIS29; break;
                case 243: mapGrid[r][c] = BlockType::TENNIS30; break;
                case 244: mapGrid[r][c] = BlockType::TENNIS31; break;
                case 245: mapGrid[r][c] = BlockType::TENNIS32; break;
                case 246: mapGrid[r][c] = BlockType::TENNIS33; break;
                case 247: mapGrid[r][c] = BlockType::TENNIS34; break;
                case 248: mapGrid[r][c] = BlockType::TENNIS35; break;
                case 249: mapGrid[r][c] = BlockType::TENNIS36; break;
                case 250: mapGrid[r][c] = BlockType::TENNIS37; break;
                case 251: mapGrid[r][c] = BlockType::TENNIS38; break;
                case 252: mapGrid[r][c] = BlockType::TENNIS39; break;
                case 253: mapGrid[r][c] = BlockType::TENNIS40; break;
                case 254: mapGrid[r][c] = BlockType::TENNIS41; break;
                case 255: mapGrid[r][c] = BlockType::TENNIS42; break;

                case 465: mapGrid[r][c] = BlockType::CODE1; break;

                case 256: mapGrid[r][c] = BlockType::CODE2; break;
                case 257: mapGrid[r][c] = BlockType::CODE3; break;
                case 258: mapGrid[r][c] = BlockType::CODE4; break;
                case 259: mapGrid[r][c] = BlockType::CODE5; break;
                case 260: mapGrid[r][c] = BlockType::CODE6; break;
                case 261: mapGrid[r][c] = BlockType::CODE7; break;
                case 262: mapGrid[r][c] = BlockType::CODE8; break;
                case 263: mapGrid[r][c] = BlockType::CODE9; break;
                case 264: mapGrid[r][c] = BlockType::CODE10; break;
                case 265: mapGrid[r][c] = BlockType::CODE11; break;
                case 266: mapGrid[r][c] = BlockType::CODE12; break;
                case 267: mapGrid[r][c] = BlockType::CODE13; break;
                case 268: mapGrid[r][c] = BlockType::CODE14; break;
                case 269: mapGrid[r][c] = BlockType::CODE15; break;
                case 270: mapGrid[r][c] = BlockType::CODE16; break;
                case 271: mapGrid[r][c] = BlockType::CODE17; break;
                case 272: mapGrid[r][c] = BlockType::CODE18; break;
                case 273: mapGrid[r][c] = BlockType::CODE19; break;
                case 274: mapGrid[r][c] = BlockType::CODE20; break;
                case 275: mapGrid[r][c] = BlockType::CODE21; break;
                case 276: mapGrid[r][c] = BlockType::CODE22; break;
                case 277: mapGrid[r][c] = BlockType::CODE23; break;
                case 278: mapGrid[r][c] = BlockType::CODE24; break;
                case 279: mapGrid[r][c] = BlockType::CODE25; break;
                case 280: mapGrid[r][c] = BlockType::CODE26; break;
                case 281: mapGrid[r][c] = BlockType::CODE27; break;
                case 282: mapGrid[r][c] = BlockType::CODE28; break;
                case 283: mapGrid[r][c] = BlockType::CODE29; break;
                case 284: mapGrid[r][c] = BlockType::CODE30; break;

                case 285: mapGrid[r][c] = BlockType::HAM1; break;
                case 286: mapGrid[r][c] = BlockType::HAM2; break;
                case 287: mapGrid[r][c] = BlockType::HAM3; break;
                case 288: mapGrid[r][c] = BlockType::HAM4; break;
                case 289: mapGrid[r][c] = BlockType::HAM5; break;
                case 290: mapGrid[r][c] = BlockType::HAM6; break;
                case 291: mapGrid[r][c] = BlockType::HAM7; break;
                case 292: mapGrid[r][c] = BlockType::HAM8; break;
                case 293: mapGrid[r][c] = BlockType::HAM9; break;
                case 294: mapGrid[r][c] = BlockType::HAM10; break;
                case 295: mapGrid[r][c] = BlockType::HAM11; break;
                case 296: mapGrid[r][c] = BlockType::HAM12; break;
                case 297: mapGrid[r][c] = BlockType::HAM13; break;
                case 298: mapGrid[r][c] = BlockType::HAM14; break;
                case 299: mapGrid[r][c] = BlockType::HAM15; break;
                case 300: mapGrid[r][c] = BlockType::HAM16; break;
                case 301: mapGrid[r][c] = BlockType::HAM17; break;
                case 302: mapGrid[r][c] = BlockType::HAM18; break;
                case 303: mapGrid[r][c] = BlockType::HAM19; break;
                case 304: mapGrid[r][c] = BlockType::HAM20; break;
                case 305: mapGrid[r][c] = BlockType::HAM21; break;
                case 306: mapGrid[r][c] = BlockType::HAM22; break;
                case 307: mapGrid[r][c] = BlockType::HAM23; break;
                case 308: mapGrid[r][c] = BlockType::HAM24; break;
                case 309: mapGrid[r][c] = BlockType::HAM25; break;
                case 310: mapGrid[r][c] = BlockType::HAM26; break;
                case 311: mapGrid[r][c] = BlockType::HAM27; break;
                case 312: mapGrid[r][c] = BlockType::HAM28; break;
                case 313: mapGrid[r][c] = BlockType::HAM29; break;
                case 314: mapGrid[r][c] = BlockType::HAM30; break;
                case 315: mapGrid[r][c] = BlockType::HAM31; break;
                case 316: mapGrid[r][c] = BlockType::HAM32; break;
                case 317: mapGrid[r][c] = BlockType::HAM33; break;
                case 318: mapGrid[r][c] = BlockType::HAM34; break;
                case 319: mapGrid[r][c] = BlockType::HAM35; break;
                case 320: mapGrid[r][c] = BlockType::HAM36; break;

                case 321: mapGrid[r][c] = BlockType::POOL1; break;
                case 322: mapGrid[r][c] = BlockType::POOL2; break;
                case 323: mapGrid[r][c] = BlockType::POOL3; break;
                case 324: mapGrid[r][c] = BlockType::POOL4; break;
                case 325: mapGrid[r][c] = BlockType::POOL5; break;
                case 326: mapGrid[r][c] = BlockType::POOL6; break;
                case 327: mapGrid[r][c] = BlockType::POOL7; break;
                case 328: mapGrid[r][c] = BlockType::POOL8; break;
                case 329: mapGrid[r][c] = BlockType::POOL9; break;
                case 330: mapGrid[r][c] = BlockType::POOL10; break;
                case 331: mapGrid[r][c] = BlockType::POOL11; break;
                case 332: mapGrid[r][c] = BlockType::POOL12; break;
                case 333: mapGrid[r][c] = BlockType::POOL13; break;
                case 334: mapGrid[r][c] = BlockType::POOL14; break;
                case 335: mapGrid[r][c] = BlockType::POOL15; break;
                case 336: mapGrid[r][c] = BlockType::POOL16; break;
                case 337: mapGrid[r][c] = BlockType::POOL17; break;
                case 338: mapGrid[r][c] = BlockType::POOL18; break;
                case 339: mapGrid[r][c] = BlockType::POOL19; break;
                case 340: mapGrid[r][c] = BlockType::POOL20; break;
                case 341: mapGrid[r][c] = BlockType::POOL21; break;
                case 342: mapGrid[r][c] = BlockType::POOL22; break;
                case 343: mapGrid[r][c] = BlockType::POOL23; break;
                case 344: mapGrid[r][c] = BlockType::POOL24; break;
                case 345: mapGrid[r][c] = BlockType::POOL25; break;

                case 346: mapGrid[r][c] = BlockType::PARKING1; break;
                case 347: mapGrid[r][c] = BlockType::PARKING2; break;
                case 348: mapGrid[r][c] = BlockType::PARKING3; break;
                case 349: mapGrid[r][c] = BlockType::PARKING4; break;
                case 350: mapGrid[r][c] = BlockType::PARKING5; break;
                case 351: mapGrid[r][c] = BlockType::PARKING6; break;
                case 352: mapGrid[r][c] = BlockType::PARKING7; break;
                case 353: mapGrid[r][c] = BlockType::PARKING8; break;
                case 354: mapGrid[r][c] = BlockType::PARKING9; break;
                case 355: mapGrid[r][c] = BlockType::PARKING10; break;
                case 356: mapGrid[r][c] = BlockType::PARKING11; break;
                case 357: mapGrid[r][c] = BlockType::PARKING12; break;
                case 358: mapGrid[r][c] = BlockType::PARKING13; break;
                case 359: mapGrid[r][c] = BlockType::PARKING14; break;
                case 360: mapGrid[r][c] = BlockType::PARKING15; break;
                case 361: mapGrid[r][c] = BlockType::PARKING16; break;
                case 362: mapGrid[r][c] = BlockType::PARKING17; break;
                case 363: mapGrid[r][c] = BlockType::PARKING18; break;

                case 364: mapGrid[r][c] = BlockType::CLUB1; break;
                case 365: mapGrid[r][c] = BlockType::CLUB2; break;
                case 366: mapGrid[r][c] = BlockType::CLUB3; break;
                case 367: mapGrid[r][c] = BlockType::CLUB4; break;
                case 368: mapGrid[r][c] = BlockType::CLUB5; break;
                case 369: mapGrid[r][c] = BlockType::CLUB6; break;
                case 370: mapGrid[r][c] = BlockType::CLUB7; break;
                case 371: mapGrid[r][c] = BlockType::CLUB8; break;
                case 372: mapGrid[r][c] = BlockType::CLUB9; break;
                case 373: mapGrid[r][c] = BlockType::CLUB10; break;
                case 374: mapGrid[r][c] = BlockType::CLUB11; break;
                case 375: mapGrid[r][c] = BlockType::CLUB12; break;
                case 376: mapGrid[r][c] = BlockType::CLUB13; break;
                case 377: mapGrid[r][c] = BlockType::CLUB14; break;
                case 378: mapGrid[r][c] = BlockType::CLUB15; break;
                case 379: mapGrid[r][c] = BlockType::CLUB16; break;
                case 380: mapGrid[r][c] = BlockType::CLUB17; break;
                case 381: mapGrid[r][c] = BlockType::CLUB18; break;
                case 382: mapGrid[r][c] = BlockType::CLUB19; break;
                case 383: mapGrid[r][c] = BlockType::CLUB20; break;
                case 384: mapGrid[r][c] = BlockType::CLUB21; break;
                case 385: mapGrid[r][c] = BlockType::CLUB22; break;
                case 386: mapGrid[r][c] = BlockType::CLUB23; break;
                case 387: mapGrid[r][c] = BlockType::CLUB24; break;
                case 388: mapGrid[r][c] = BlockType::CLUB25; break;
                case 389: mapGrid[r][c] = BlockType::CLUB26; break;
                case 390: mapGrid[r][c] = BlockType::CLUB27; break;
                case 391: mapGrid[r][c] = BlockType::CLUB28; break;
                case 392: mapGrid[r][c] = BlockType::CLUB29; break;
                case 393: mapGrid[r][c] = BlockType::CLUB30; break;
                case 394: mapGrid[r][c] = BlockType::CLUB31; break;
                case 395: mapGrid[r][c] = BlockType::CLUB32; break;

                case 396: mapGrid[r][c] = BlockType::SHOP1; break;
                case 397: mapGrid[r][c] = BlockType::SHOP2; break;
                case 398: mapGrid[r][c] = BlockType::SHOP3; break;
                case 399: mapGrid[r][c] = BlockType::SHOP4; break;
                case 400: mapGrid[r][c] = BlockType::SHOP5; break;
                case 401: mapGrid[r][c] = BlockType::SHOP6; break;
                case 402: mapGrid[r][c] = BlockType::SHOP7; break;
                case 403: mapGrid[r][c] = BlockType::SHOP8; break;
                case 404: mapGrid[r][c] = BlockType::SHOP9; break;

                case 405: mapGrid[r][c] = BlockType::REST1; break;
                case 406: mapGrid[r][c] = BlockType::REST2; break;
                case 407: mapGrid[r][c] = BlockType::REST3; break;
                case 408: mapGrid[r][c] = BlockType::REST4; break;
                case 409: mapGrid[r][c] = BlockType::REST5; break;
                case 410: mapGrid[r][c] = BlockType::REST6; break;
                case 411: mapGrid[r][c] = BlockType::REST7; break;
                case 412: mapGrid[r][c] = BlockType::REST8; break;
                case 413: mapGrid[r][c] = BlockType::REST9; break;
                case 414: mapGrid[r][c] = BlockType::REST10; break;
                case 415: mapGrid[r][c] = BlockType::REST11; break;
                case 416: mapGrid[r][c] = BlockType::REST12; break;

                case 417: mapGrid[r][c] = BlockType::CASTLE1; break;
                case 418: mapGrid[r][c] = BlockType::CASTLE2; break;
                case 419: mapGrid[r][c] = BlockType::CASTLE3; break;
                case 420: mapGrid[r][c] = BlockType::CASTLE4; break;
                case 421: mapGrid[r][c] = BlockType::CASTLE5; break;
                case 422: mapGrid[r][c] = BlockType::CASTLE6; break;
                case 423: mapGrid[r][c] = BlockType::CASTLE7; break;
                case 424: mapGrid[r][c] = BlockType::CASTLE8; break;
                case 425: mapGrid[r][c] = BlockType::CASTLE9; break;
                case 426: mapGrid[r][c] = BlockType::CASTLE10; break;
                case 427: mapGrid[r][c] = BlockType::CASTLE11; break;
                case 428: mapGrid[r][c] = BlockType::CASTLE12; break;
                case 429: mapGrid[r][c] = BlockType::CASTLE13; break;
                case 430: mapGrid[r][c] = BlockType::CASTLE14; break;
                case 431: mapGrid[r][c] = BlockType::CASTLE15; break;
                case 432: mapGrid[r][c] = BlockType::CASTLE16; break;
                case 433: mapGrid[r][c] = BlockType::CASTLE17; break;
                case 434: mapGrid[r][c] = BlockType::CASTLE18; break;
                case 435: mapGrid[r][c] = BlockType::CASTLE19; break;
                case 436: mapGrid[r][c] = BlockType::CASTLE20; break;
                case 437: mapGrid[r][c] = BlockType::CASTLE21; break;
                case 438: mapGrid[r][c] = BlockType::CASTLE22; break;
                case 439: mapGrid[r][c] = BlockType::CASTLE23; break;
                case 440: mapGrid[r][c] = BlockType::CASTLE24; break;
                case 441: mapGrid[r][c] = BlockType::CASTLE25; break;
                case 442: mapGrid[r][c] = BlockType::CASTLE26; break;
                case 443: mapGrid[r][c] = BlockType::CASTLE27; break;
                case 444: mapGrid[r][c] = BlockType::CASTLE28; break;
                case 445: mapGrid[r][c] = BlockType::CASTLE29; break;
                case 446: mapGrid[r][c] = BlockType::CASTLE30; break;
                case 447: mapGrid[r][c] = BlockType::CASTLE31; break;
                case 448: mapGrid[r][c] = BlockType::CASTLE32; break;
                case 449: mapGrid[r][c] = BlockType::CASTLE33; break;
                case 450: mapGrid[r][c] = BlockType::CASTLE34; break;
                case 451: mapGrid[r][c] = BlockType::CASTLE35; break;
                case 452: mapGrid[r][c] = BlockType::CASTLE36; break;
                case 453: mapGrid[r][c] = BlockType::CASTLE37; break;
                case 454: mapGrid[r][c] = BlockType::CASTLE38; break;
                case 455: mapGrid[r][c] = BlockType::CASTLE39; break;
                case 456: mapGrid[r][c] = BlockType::CASTLE40; break;
                case 457: mapGrid[r][c] = BlockType::CASTLE41; break;
                case 458: mapGrid[r][c] = BlockType::CASTLE42; break;
                case 459: mapGrid[r][c] = BlockType::CASTLE43; break;
                case 460: mapGrid[r][c] = BlockType::CASTLE44; break;
                case 461: mapGrid[r][c] = BlockType::CASTLE45; break;
                case 462: mapGrid[r][c] = BlockType::CASTLE46; break;
                case 463: mapGrid[r][c] = BlockType::CASTLE47; break;
                case 464: mapGrid[r][c] = BlockType::CASTLE48; break;

                case 466: mapGrid[r][c] = BlockType::COFFEE1; break;
                case 467: mapGrid[r][c] = BlockType::COFFEE2; break;
                case 468: mapGrid[r][c] = BlockType::COFFEE3; break;
                case 469: mapGrid[r][c] = BlockType::COFFEE4; break;
                case 470: mapGrid[r][c] = BlockType::COFFEE5; break;
                case 471: mapGrid[r][c] = BlockType::COFFEE6; break;
                case 472: mapGrid[r][c] = BlockType::COFFEE7; break;
                case 473: mapGrid[r][c] = BlockType::COFFEE8; break;
                case 474: mapGrid[r][c] = BlockType::COFFEE9; break;
                case 475: mapGrid[r][c] = BlockType::COFFEE10; break;
                case 476: mapGrid[r][c] = BlockType::COFFEE11; break;
                case 477: mapGrid[r][c] = BlockType::COFFEE12; break;
                case 478: mapGrid[r][c] = BlockType::COFFEE13; break;
                case 479: mapGrid[r][c] = BlockType::COFFEE14; break;
                case 480: mapGrid[r][c] = BlockType::COFFEE15; break;
                case 481: mapGrid[r][c] = BlockType::COFFEE16; break;
                case 482: mapGrid[r][c] = BlockType::COFFEE17; break;
                case 483: mapGrid[r][c] = BlockType::COFFEE18; break;
                case 484: mapGrid[r][c] = BlockType::COFFEE19; break;
                case 485: mapGrid[r][c] = BlockType::COFFEE20; break;
                case 486: mapGrid[r][c] = BlockType::COFFEE21; break;
                case 487: mapGrid[r][c] = BlockType::COFFEE22; break;
                case 488: mapGrid[r][c] = BlockType::COFFEE23; break;
                case 489: mapGrid[r][c] = BlockType::COFFEE24; break;

                case 490: mapGrid[r][c] = BlockType::GRASS1; break;
                case 491: mapGrid[r][c] = BlockType::GRASS2; break;
                case 492: mapGrid[r][c] = BlockType::GRASS3; break;
                case 493: mapGrid[r][c] = BlockType::GRASS4; break;
                case 494: mapGrid[r][c] = BlockType::GRASS5; break;
                case 495: mapGrid[r][c] = BlockType::GRASS6; break;
                case 496: mapGrid[r][c] = BlockType::GRASS7; break;
                case 497: mapGrid[r][c] = BlockType::GRASS8; break;
                case 498: mapGrid[r][c] = BlockType::GRASS9; break;
                case 499: mapGrid[r][c] = BlockType::GRASS10; break;
                case 500: mapGrid[r][c] = BlockType::GRASS11; break;
                case 501: mapGrid[r][c] = BlockType::GRASS12; break;
                case 502: mapGrid[r][c] = BlockType::GRASS13; break;
                case 503: mapGrid[r][c] = BlockType::GRASS14; break;
                case 504: mapGrid[r][c] = BlockType::GRASS15; break;
                case 505: mapGrid[r][c] = BlockType::GRASS16; break;
                case 506: mapGrid[r][c] = BlockType::GRASS17; break;
                case 507: mapGrid[r][c] = BlockType::GRASS18; break;
                case 508: mapGrid[r][c] = BlockType::GRASS19; break;
                case 509: mapGrid[r][c] = BlockType::GRASS20; break;
                case 510: mapGrid[r][c] = BlockType::GRASS21; break;
                case 511: mapGrid[r][c] = BlockType::GRASS22; break;
                case 512: mapGrid[r][c] = BlockType::GRASS23; break;
                case 513: mapGrid[r][c] = BlockType::GRASS24; break;

                
                default:  
                    if (!file) {
                        std::cerr << "Error reading tile at (" << r << "," << c << ")." << std::endl;
                        throw std::ios_base::failure("Map data is corrupted.");
                    }
                    mapGrid[r][c] = BlockType::NOTHING;
                    break;
            }
            std::cerr << "[DEBUG] Map loaded: " << r << " rows, " << c << " cols="<<tile<<'\n';
        }
        
    }
    tiles = mapGrid;
    
    std::cerr << "[DEBUG] Map loaded: " << rows << " rows, " << cols << " cols.\n";
    std::cerr << "[DEBUG] Map loaded: " << rows << " rows, " << cols << " cols.\n";
    std::cerr << "[DEBUG] mapGrid size: " << mapGrid.size() << " * " 
          << (mapGrid.empty() ? 0 : mapGrid[0].size()) << std::endl;

    
    // 假設檔案接著還有產生點、敵人資料等
    // ...
}




void Map::draw() {
    // 用 Allegro 畫出可視範圍的地圖 tiles
    // cameraPos 代表相機(玩家視角)左上角的座標

     // 假設每格32x32像素

    Engine::Point cameraPos = scene->getCam();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int drawX = c * tileSize - cameraPos.x;
            int drawY = r * tileSize - cameraPos.y;

            // 這裡依據 mapGrid[r][c] 繪製相應圖片
            // 假設 tileset 分割好，每種 BlockType 對應一塊圖
            BlockType type = mapGrid[r][c];
            //BlockType type = tiles[r][c];
            //if (type != BlockType::NOTHING) {
                // 例如：
                // al_draw_bitmap_region(tileset, srcX, srcY, tileSize, tileSize, drawX, drawY, 0);
            //}

            // 繪製硬幣動畫（如果有）
            //if (coinStatus[r][c] == CoinStatus::APPEAR) {
                // al_draw_bitmap_region(coinSprites, frameX, frameY, ..., drawX, drawY, 0);
            //}

            if (type == BlockType::FLOOR) {
                // 例如：
                // al_draw_bitmap_region(tileset, srcX, srcY, tileSize, tileSize, drawX, drawY, 0);
                al_draw_scaled_bitmap(tileSet[0]->bmp.get(), // image 
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );
            }
            else if (type == BlockType::WALL) {

                al_draw_scaled_bitmap(tileSet[1]->bmp.get(), // image
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );
            }
            else if (type == BlockType::TREE1) {

                /*al_draw_scaled_bitmap(tileSet[2]->bmp.get(), // image
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );*/
                ALLEGRO_BITMAP* bmp = tileSet[2]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND1) {

                ALLEGRO_BITMAP* bmp = tileSet[3]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND2) {

                ALLEGRO_BITMAP* bmp = tileSet[4]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND3) {

                ALLEGRO_BITMAP* bmp = tileSet[5]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND4) {

                ALLEGRO_BITMAP* bmp = tileSet[6]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND5) {

                ALLEGRO_BITMAP* bmp = tileSet[7]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND6) {

                ALLEGRO_BITMAP* bmp = tileSet[8]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND7) {

                ALLEGRO_BITMAP* bmp = tileSet[9]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND8) {

                ALLEGRO_BITMAP* bmp = tileSet[10]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND9) {

                ALLEGRO_BITMAP* bmp = tileSet[11]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND10) {

                ALLEGRO_BITMAP* bmp = tileSet[12]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND11) {

                ALLEGRO_BITMAP* bmp = tileSet[13]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND12) {

                ALLEGRO_BITMAP* bmp = tileSet[14]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND13) {

                ALLEGRO_BITMAP* bmp = tileSet[15]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND14) {

                ALLEGRO_BITMAP* bmp = tileSet[16]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND15) {

                ALLEGRO_BITMAP* bmp = tileSet[17]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND16) {

                ALLEGRO_BITMAP* bmp = tileSet[18]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

                                    
            }
            else if (type == BlockType::GROUND17) {

                ALLEGRO_BITMAP* bmp = tileSet[19]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND18) {

                ALLEGRO_BITMAP* bmp = tileSet[20]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND19) {

                ALLEGRO_BITMAP* bmp = tileSet[21]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND20) {

                ALLEGRO_BITMAP* bmp = tileSet[22]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND21) {

                ALLEGRO_BITMAP* bmp = tileSet[23]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND22) {

                ALLEGRO_BITMAP* bmp = tileSet[24]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND23) {

                ALLEGRO_BITMAP* bmp = tileSet[25]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND24) {

                ALLEGRO_BITMAP* bmp = tileSet[26]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND25) {

                ALLEGRO_BITMAP* bmp = tileSet[27]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND26) {

                ALLEGRO_BITMAP* bmp = tileSet[28]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND27) {

                ALLEGRO_BITMAP* bmp = tileSet[29]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND28) {

                ALLEGRO_BITMAP* bmp = tileSet[30]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND29) {

                ALLEGRO_BITMAP* bmp = tileSet[31]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND30) {

                ALLEGRO_BITMAP* bmp = tileSet[32]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND31) {

                ALLEGRO_BITMAP* bmp = tileSet[33]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND32) {

                ALLEGRO_BITMAP* bmp = tileSet[34]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND33) {

                ALLEGRO_BITMAP* bmp = tileSet[35]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND34) {

                ALLEGRO_BITMAP* bmp = tileSet[36]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND35) {

                ALLEGRO_BITMAP* bmp = tileSet[37]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND36) {

                ALLEGRO_BITMAP* bmp = tileSet[168]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND37) {

                ALLEGRO_BITMAP* bmp = tileSet[169]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND38) {

                ALLEGRO_BITMAP* bmp = tileSet[170]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND39) {

                ALLEGRO_BITMAP* bmp = tileSet[171]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND40) {

                ALLEGRO_BITMAP* bmp = tileSet[172]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND41) {

                ALLEGRO_BITMAP* bmp = tileSet[173]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GROUND42) {

                ALLEGRO_BITMAP* bmp = tileSet[174]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING1) {

                ALLEGRO_BITMAP* bmp = tileSet[38]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING2) {

                ALLEGRO_BITMAP* bmp = tileSet[39]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING3) {

                ALLEGRO_BITMAP* bmp = tileSet[40]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING4) {

                ALLEGRO_BITMAP* bmp = tileSet[41]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING5) {

                ALLEGRO_BITMAP* bmp = tileSet[42]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING6) {

                ALLEGRO_BITMAP* bmp = tileSet[43]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING7) {

                ALLEGRO_BITMAP* bmp = tileSet[44]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING8) {

                ALLEGRO_BITMAP* bmp = tileSet[45]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING9) {

                ALLEGRO_BITMAP* bmp = tileSet[46]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING10) {

                ALLEGRO_BITMAP* bmp = tileSet[47]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING11) {

                ALLEGRO_BITMAP* bmp = tileSet[48]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING12) {

                ALLEGRO_BITMAP* bmp = tileSet[49]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING13) {

                ALLEGRO_BITMAP* bmp = tileSet[50]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING14) {

                ALLEGRO_BITMAP* bmp = tileSet[51]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING15) {

                ALLEGRO_BITMAP* bmp = tileSet[52]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING16) {

                ALLEGRO_BITMAP* bmp = tileSet[53]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING17) {

                ALLEGRO_BITMAP* bmp = tileSet[54]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING18) {

                ALLEGRO_BITMAP* bmp = tileSet[55]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING19) {

                ALLEGRO_BITMAP* bmp = tileSet[56]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING20) {

                ALLEGRO_BITMAP* bmp = tileSet[57]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING21) {

                ALLEGRO_BITMAP* bmp = tileSet[58]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING22) {

                ALLEGRO_BITMAP* bmp = tileSet[59]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING23) {

                ALLEGRO_BITMAP* bmp = tileSet[60]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING24) {

                ALLEGRO_BITMAP* bmp = tileSet[61]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING25) {

                ALLEGRO_BITMAP* bmp = tileSet[62]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING26) {

                ALLEGRO_BITMAP* bmp = tileSet[63]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING27) {

                ALLEGRO_BITMAP* bmp = tileSet[64]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING28) {

                ALLEGRO_BITMAP* bmp = tileSet[65]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING29) {

                ALLEGRO_BITMAP* bmp = tileSet[66]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING30) {

                ALLEGRO_BITMAP* bmp = tileSet[67]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING31) {

                ALLEGRO_BITMAP* bmp = tileSet[68]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING32) {

                ALLEGRO_BITMAP* bmp = tileSet[69]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING33) {

                ALLEGRO_BITMAP* bmp = tileSet[70]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING34) {

                ALLEGRO_BITMAP* bmp = tileSet[71]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING35) {

                ALLEGRO_BITMAP* bmp = tileSet[72]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING36) {

                ALLEGRO_BITMAP* bmp = tileSet[73]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING37) {

                ALLEGRO_BITMAP* bmp = tileSet[74]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING38) {

                ALLEGRO_BITMAP* bmp = tileSet[75]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                


            }
            else if (type == BlockType::CSBUILDING39) {

                ALLEGRO_BITMAP* bmp = tileSet[76]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING40) {

                ALLEGRO_BITMAP* bmp = tileSet[77]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING41) {

                ALLEGRO_BITMAP* bmp = tileSet[78]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING42) {

                ALLEGRO_BITMAP* bmp = tileSet[79]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING43) {

                ALLEGRO_BITMAP* bmp = tileSet[80]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING44) {

                ALLEGRO_BITMAP* bmp = tileSet[81]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING45) {

                ALLEGRO_BITMAP* bmp = tileSet[82]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING46) {

                ALLEGRO_BITMAP* bmp = tileSet[83]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING47) {

                ALLEGRO_BITMAP* bmp = tileSet[84]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING48) {

                ALLEGRO_BITMAP* bmp = tileSet[85]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING49) {

                ALLEGRO_BITMAP* bmp = tileSet[86]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CSBUILDING50) {

                ALLEGRO_BITMAP* bmp = tileSet[87]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE1) {

                ALLEGRO_BITMAP* bmp = tileSet[89]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE2) {

                ALLEGRO_BITMAP* bmp = tileSet[90]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE3) {

                ALLEGRO_BITMAP* bmp = tileSet[91]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE4) {

                ALLEGRO_BITMAP* bmp = tileSet[92]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE5) {

                ALLEGRO_BITMAP* bmp = tileSet[93]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE6) {

                ALLEGRO_BITMAP* bmp = tileSet[94]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE7) {

                ALLEGRO_BITMAP* bmp = tileSet[95]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE8) {

                ALLEGRO_BITMAP* bmp = tileSet[96]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE9) {

                ALLEGRO_BITMAP* bmp = tileSet[97]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE10) {

                ALLEGRO_BITMAP* bmp = tileSet[98]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE11) {

                ALLEGRO_BITMAP* bmp = tileSet[99]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE12) {

                ALLEGRO_BITMAP* bmp = tileSet[100]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE13) {

                ALLEGRO_BITMAP* bmp = tileSet[101]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE14) {

                ALLEGRO_BITMAP* bmp = tileSet[102]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE15) {

                ALLEGRO_BITMAP* bmp = tileSet[103]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE16) {

                ALLEGRO_BITMAP* bmp = tileSet[104]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE17) {

                ALLEGRO_BITMAP* bmp = tileSet[105]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE18) {

                ALLEGRO_BITMAP* bmp = tileSet[106]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE19) {

                ALLEGRO_BITMAP* bmp = tileSet[107]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE20) {

                ALLEGRO_BITMAP* bmp = tileSet[108]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE21) {

                ALLEGRO_BITMAP* bmp = tileSet[109]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE22) {

                ALLEGRO_BITMAP* bmp = tileSet[110]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE23) {

                ALLEGRO_BITMAP* bmp = tileSet[111]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE24) {

                ALLEGRO_BITMAP* bmp = tileSet[112]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LAKE25) {

                ALLEGRO_BITMAP* bmp = tileSet[113]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            
            else if (type == BlockType::LIBRARY1) {

                ALLEGRO_BITMAP* bmp = tileSet[119]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY2) {

                ALLEGRO_BITMAP* bmp = tileSet[120]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY3) {

                ALLEGRO_BITMAP* bmp = tileSet[121]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY4) {

                ALLEGRO_BITMAP* bmp = tileSet[122]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY5) {

                ALLEGRO_BITMAP* bmp = tileSet[123]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY6) {

                ALLEGRO_BITMAP* bmp = tileSet[124]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY7) {

                ALLEGRO_BITMAP* bmp = tileSet[125]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY8) {

                ALLEGRO_BITMAP* bmp = tileSet[126]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY9) {

                ALLEGRO_BITMAP* bmp = tileSet[127]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY10) {

                ALLEGRO_BITMAP* bmp = tileSet[128]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY11) {

                ALLEGRO_BITMAP* bmp = tileSet[129]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY12) {

                ALLEGRO_BITMAP* bmp = tileSet[130]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY13) {

                ALLEGRO_BITMAP* bmp = tileSet[131]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY14) {

                ALLEGRO_BITMAP* bmp = tileSet[132]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY15) {

                ALLEGRO_BITMAP* bmp = tileSet[133]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY16) {

                ALLEGRO_BITMAP* bmp = tileSet[134]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY17) {

                ALLEGRO_BITMAP* bmp = tileSet[135]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY18) {

                ALLEGRO_BITMAP* bmp = tileSet[136]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY19) {

                ALLEGRO_BITMAP* bmp = tileSet[137]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY20) {

                ALLEGRO_BITMAP* bmp = tileSet[138]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY21) {

                ALLEGRO_BITMAP* bmp = tileSet[139]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY22) {

                ALLEGRO_BITMAP* bmp = tileSet[140]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY23) {

                ALLEGRO_BITMAP* bmp = tileSet[141]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY24) {

                ALLEGRO_BITMAP* bmp = tileSet[142]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY25) {

                ALLEGRO_BITMAP* bmp = tileSet[143]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY26) {

                ALLEGRO_BITMAP* bmp = tileSet[144]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY27) {

                ALLEGRO_BITMAP* bmp = tileSet[145]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY28) {

                ALLEGRO_BITMAP* bmp = tileSet[146]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY29) {

                ALLEGRO_BITMAP* bmp = tileSet[147]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY30) {

                ALLEGRO_BITMAP* bmp = tileSet[148]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY31) {

                ALLEGRO_BITMAP* bmp = tileSet[149]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY32) {

                ALLEGRO_BITMAP* bmp = tileSet[150]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY33) {

                ALLEGRO_BITMAP* bmp = tileSet[151]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY34) {

                ALLEGRO_BITMAP* bmp = tileSet[152]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY35) {

                ALLEGRO_BITMAP* bmp = tileSet[153]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY36) {

                ALLEGRO_BITMAP* bmp = tileSet[154]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY37) {

                ALLEGRO_BITMAP* bmp = tileSet[155]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY38) {

                ALLEGRO_BITMAP* bmp = tileSet[156]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY39) {

                ALLEGRO_BITMAP* bmp = tileSet[157]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY40) {

                ALLEGRO_BITMAP* bmp = tileSet[158]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY41) {

                ALLEGRO_BITMAP* bmp = tileSet[159]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY42) {

                ALLEGRO_BITMAP* bmp = tileSet[160]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY43) {

                ALLEGRO_BITMAP* bmp = tileSet[161]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY44) {

                ALLEGRO_BITMAP* bmp = tileSet[162]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY45) {

                ALLEGRO_BITMAP* bmp = tileSet[163]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY46) {

                ALLEGRO_BITMAP* bmp = tileSet[164]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY47) {

                ALLEGRO_BITMAP* bmp = tileSet[165]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::LIBRARY48) {

                ALLEGRO_BITMAP* bmp = tileSet[166]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS1) {

                ALLEGRO_BITMAP* bmp = tileSet[167]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            
           else if (type == BlockType::QINLAKE1) {

                ALLEGRO_BITMAP* bmp = tileSet[175]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE2) {

                ALLEGRO_BITMAP* bmp = tileSet[176]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE3) {

                ALLEGRO_BITMAP* bmp = tileSet[177]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE4) {

                ALLEGRO_BITMAP* bmp = tileSet[178]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE5) {

                ALLEGRO_BITMAP* bmp = tileSet[179]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE6) {

                ALLEGRO_BITMAP* bmp = tileSet[180]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE7) {

                ALLEGRO_BITMAP* bmp = tileSet[181]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE8) {

                ALLEGRO_BITMAP* bmp = tileSet[182]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE9) {

                ALLEGRO_BITMAP* bmp = tileSet[183]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE10) {

                ALLEGRO_BITMAP* bmp = tileSet[184]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE11) {

                ALLEGRO_BITMAP* bmp = tileSet[185]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE12) {

                ALLEGRO_BITMAP* bmp = tileSet[186]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE13) {

                ALLEGRO_BITMAP* bmp = tileSet[187]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE14) {

                ALLEGRO_BITMAP* bmp = tileSet[188]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE15) {

                ALLEGRO_BITMAP* bmp = tileSet[189]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE16) {

                ALLEGRO_BITMAP* bmp = tileSet[190]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE17) {

                ALLEGRO_BITMAP* bmp = tileSet[191]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE18) {

                ALLEGRO_BITMAP* bmp = tileSet[192]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE19) {

                ALLEGRO_BITMAP* bmp = tileSet[193]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE20) {

                ALLEGRO_BITMAP* bmp = tileSet[194]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE21) {

                ALLEGRO_BITMAP* bmp = tileSet[195]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE22) {

                ALLEGRO_BITMAP* bmp = tileSet[196]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE23) {

                ALLEGRO_BITMAP* bmp = tileSet[197]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE24) {

                ALLEGRO_BITMAP* bmp = tileSet[198]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE25) {

                ALLEGRO_BITMAP* bmp = tileSet[199]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE26) {

                ALLEGRO_BITMAP* bmp = tileSet[200]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE27) {

                ALLEGRO_BITMAP* bmp = tileSet[201]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE28) {

                ALLEGRO_BITMAP* bmp = tileSet[202]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE29) {

                ALLEGRO_BITMAP* bmp = tileSet[203]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE30) {

                ALLEGRO_BITMAP* bmp = tileSet[204]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE31) {

                ALLEGRO_BITMAP* bmp = tileSet[205]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE32) {

                ALLEGRO_BITMAP* bmp = tileSet[206]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE33) {

                ALLEGRO_BITMAP* bmp = tileSet[207]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE34) {

                ALLEGRO_BITMAP* bmp = tileSet[208]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE35) {

                ALLEGRO_BITMAP* bmp = tileSet[209]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE36) {

                ALLEGRO_BITMAP* bmp = tileSet[210]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE37) {

                ALLEGRO_BITMAP* bmp = tileSet[211]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE38) {

                ALLEGRO_BITMAP* bmp = tileSet[212]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE39) {

                ALLEGRO_BITMAP* bmp = tileSet[213]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::QINLAKE40) {

                ALLEGRO_BITMAP* bmp = tileSet[214]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS2) {

                ALLEGRO_BITMAP* bmp = tileSet[215]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS3) {

                ALLEGRO_BITMAP* bmp = tileSet[216]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS4) {

                ALLEGRO_BITMAP* bmp = tileSet[217]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS5) {

                ALLEGRO_BITMAP* bmp = tileSet[218]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS6) {

                ALLEGRO_BITMAP* bmp = tileSet[219]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS7) {

                ALLEGRO_BITMAP* bmp = tileSet[220]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS8) {

                ALLEGRO_BITMAP* bmp = tileSet[221]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS9) {

                ALLEGRO_BITMAP* bmp = tileSet[222]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS10) {

                ALLEGRO_BITMAP* bmp = tileSet[223]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS11) {

                ALLEGRO_BITMAP* bmp = tileSet[224]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS12) {

                ALLEGRO_BITMAP* bmp = tileSet[225]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS13) {

                ALLEGRO_BITMAP* bmp = tileSet[226]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS14) {

                ALLEGRO_BITMAP* bmp = tileSet[227]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS15) {

                ALLEGRO_BITMAP* bmp = tileSet[228]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS16) {

                ALLEGRO_BITMAP* bmp = tileSet[229]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS17) {

                ALLEGRO_BITMAP* bmp = tileSet[230]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS18) {

                ALLEGRO_BITMAP* bmp = tileSet[231]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS19) {

                ALLEGRO_BITMAP* bmp = tileSet[232]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS20) {

                ALLEGRO_BITMAP* bmp = tileSet[233]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS21) {

                ALLEGRO_BITMAP* bmp = tileSet[234]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS22) {

                ALLEGRO_BITMAP* bmp = tileSet[235]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS23) {

                ALLEGRO_BITMAP* bmp = tileSet[236]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS24) {

                ALLEGRO_BITMAP* bmp = tileSet[237]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS25) {

                ALLEGRO_BITMAP* bmp = tileSet[238]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS26) {

                ALLEGRO_BITMAP* bmp = tileSet[239]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS27) {

                ALLEGRO_BITMAP* bmp = tileSet[240]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS28) {

                ALLEGRO_BITMAP* bmp = tileSet[241]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS29) {

                ALLEGRO_BITMAP* bmp = tileSet[242]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS30) {

                ALLEGRO_BITMAP* bmp = tileSet[243]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS31) {

                ALLEGRO_BITMAP* bmp = tileSet[244]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS32) {

                ALLEGRO_BITMAP* bmp = tileSet[245]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS33) {

                ALLEGRO_BITMAP* bmp = tileSet[246]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS34) {

                ALLEGRO_BITMAP* bmp = tileSet[247]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS35) {

                ALLEGRO_BITMAP* bmp = tileSet[248]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS36) {

                ALLEGRO_BITMAP* bmp = tileSet[249]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS37) {

                ALLEGRO_BITMAP* bmp = tileSet[250]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS38) {

                ALLEGRO_BITMAP* bmp = tileSet[251]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS39) {

                ALLEGRO_BITMAP* bmp = tileSet[252]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS40) {

                ALLEGRO_BITMAP* bmp = tileSet[253]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS41) {

                ALLEGRO_BITMAP* bmp = tileSet[254]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::TENNIS42) {

                ALLEGRO_BITMAP* bmp = tileSet[255]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            
            else if (type == BlockType::CODE1) {

                ALLEGRO_BITMAP* bmp = tileSet[465]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE2) {

                ALLEGRO_BITMAP* bmp = tileSet[256]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE3) {

                ALLEGRO_BITMAP* bmp = tileSet[257]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE4) {

                ALLEGRO_BITMAP* bmp = tileSet[258]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE5) {

                ALLEGRO_BITMAP* bmp = tileSet[259]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE6) {

                ALLEGRO_BITMAP* bmp = tileSet[260]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE7) {

                ALLEGRO_BITMAP* bmp = tileSet[261]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE8) {

                ALLEGRO_BITMAP* bmp = tileSet[262]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE9) {

                ALLEGRO_BITMAP* bmp = tileSet[263]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE10) {

                ALLEGRO_BITMAP* bmp = tileSet[264]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE11) {

                ALLEGRO_BITMAP* bmp = tileSet[265]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE12) {

                ALLEGRO_BITMAP* bmp = tileSet[266]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE13) {

                ALLEGRO_BITMAP* bmp = tileSet[267]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE14) {

                ALLEGRO_BITMAP* bmp = tileSet[268]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE15) {

                ALLEGRO_BITMAP* bmp = tileSet[269]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE16) {

                ALLEGRO_BITMAP* bmp = tileSet[270]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE17) {

                ALLEGRO_BITMAP* bmp = tileSet[271]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE18) {

                ALLEGRO_BITMAP* bmp = tileSet[272]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE19) {

                ALLEGRO_BITMAP* bmp = tileSet[273]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE20) {

                ALLEGRO_BITMAP* bmp = tileSet[274]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE21) {

                ALLEGRO_BITMAP* bmp = tileSet[275]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE22) {

                ALLEGRO_BITMAP* bmp = tileSet[276]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE23) {

                ALLEGRO_BITMAP* bmp = tileSet[277]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE24) {

                ALLEGRO_BITMAP* bmp = tileSet[278]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE25) {

                ALLEGRO_BITMAP* bmp = tileSet[279]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE26) {

                ALLEGRO_BITMAP* bmp = tileSet[280]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE27) {

                ALLEGRO_BITMAP* bmp = tileSet[281]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE28) {

                ALLEGRO_BITMAP* bmp = tileSet[282]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE29) {

                ALLEGRO_BITMAP* bmp = tileSet[283]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CODE30) {

                ALLEGRO_BITMAP* bmp = tileSet[284]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM1) {

                ALLEGRO_BITMAP* bmp = tileSet[285]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM2) {

                ALLEGRO_BITMAP* bmp = tileSet[286]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM3) {

                ALLEGRO_BITMAP* bmp = tileSet[287]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM4) {

                ALLEGRO_BITMAP* bmp = tileSet[288]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM5) {

                ALLEGRO_BITMAP* bmp = tileSet[289]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM6) {

                ALLEGRO_BITMAP* bmp = tileSet[290]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM7) {

                ALLEGRO_BITMAP* bmp = tileSet[291]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM8) {

                ALLEGRO_BITMAP* bmp = tileSet[292]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM9) {

                ALLEGRO_BITMAP* bmp = tileSet[293]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM10) {

                ALLEGRO_BITMAP* bmp = tileSet[294]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM11) {

                ALLEGRO_BITMAP* bmp = tileSet[295]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM12) {

                ALLEGRO_BITMAP* bmp = tileSet[296]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM13) {

                ALLEGRO_BITMAP* bmp = tileSet[297]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM14) {

                ALLEGRO_BITMAP* bmp = tileSet[298]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM15) {

                ALLEGRO_BITMAP* bmp = tileSet[299]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM16) {

                ALLEGRO_BITMAP* bmp = tileSet[300]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM17) {

                ALLEGRO_BITMAP* bmp = tileSet[301]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM18) {

                ALLEGRO_BITMAP* bmp = tileSet[302]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM19) {

                ALLEGRO_BITMAP* bmp = tileSet[303]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM20) {

                ALLEGRO_BITMAP* bmp = tileSet[304]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM21) {

                ALLEGRO_BITMAP* bmp = tileSet[305]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM22) {

                ALLEGRO_BITMAP* bmp = tileSet[306]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM23) {

                ALLEGRO_BITMAP* bmp = tileSet[307]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM24) {

                ALLEGRO_BITMAP* bmp = tileSet[308]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM25) {

                ALLEGRO_BITMAP* bmp = tileSet[309]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM26) {

                ALLEGRO_BITMAP* bmp = tileSet[310]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM27) {

                ALLEGRO_BITMAP* bmp = tileSet[311]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM28) {

                ALLEGRO_BITMAP* bmp = tileSet[312]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM29) {

                ALLEGRO_BITMAP* bmp = tileSet[313]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM30) {

                ALLEGRO_BITMAP* bmp = tileSet[314]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM31) {

                ALLEGRO_BITMAP* bmp = tileSet[315]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM32) {

                ALLEGRO_BITMAP* bmp = tileSet[316]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM33) {

                ALLEGRO_BITMAP* bmp = tileSet[317]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM34) {

                ALLEGRO_BITMAP* bmp = tileSet[318]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM35) {

                ALLEGRO_BITMAP* bmp = tileSet[319]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HAM36) {

                ALLEGRO_BITMAP* bmp = tileSet[320]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            
            
            else if (type == BlockType::POOL1) {

                ALLEGRO_BITMAP* bmp = tileSet[321]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL2) {

                ALLEGRO_BITMAP* bmp = tileSet[322]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL3) {

                ALLEGRO_BITMAP* bmp = tileSet[323]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL4) {

                ALLEGRO_BITMAP* bmp = tileSet[324]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL5) {

                ALLEGRO_BITMAP* bmp = tileSet[325]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL6) {

                ALLEGRO_BITMAP* bmp = tileSet[326]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL7) {

                ALLEGRO_BITMAP* bmp = tileSet[327]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL8) {

                ALLEGRO_BITMAP* bmp = tileSet[328]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL9) {

                ALLEGRO_BITMAP* bmp = tileSet[329]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL10) {

                ALLEGRO_BITMAP* bmp = tileSet[330]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL11) {

                ALLEGRO_BITMAP* bmp = tileSet[331]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL12) {

                ALLEGRO_BITMAP* bmp = tileSet[332]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL13) {

                ALLEGRO_BITMAP* bmp = tileSet[333]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL14) {

                ALLEGRO_BITMAP* bmp = tileSet[334]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL15) {

                ALLEGRO_BITMAP* bmp = tileSet[335]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL16) {

                ALLEGRO_BITMAP* bmp = tileSet[336]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL17) {

                ALLEGRO_BITMAP* bmp = tileSet[337]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL18) {

                ALLEGRO_BITMAP* bmp = tileSet[338]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL19) {

                ALLEGRO_BITMAP* bmp = tileSet[339]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL20) {

                ALLEGRO_BITMAP* bmp = tileSet[340]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL21) {

                ALLEGRO_BITMAP* bmp = tileSet[341]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL22) {

                ALLEGRO_BITMAP* bmp = tileSet[342]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL23) {

                ALLEGRO_BITMAP* bmp = tileSet[343]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL24) {

                ALLEGRO_BITMAP* bmp = tileSet[344]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::POOL25) {

                ALLEGRO_BITMAP* bmp = tileSet[345]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            

            else if (type == BlockType::PARKING1) {

                ALLEGRO_BITMAP* bmp = tileSet[346]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING2) {

                ALLEGRO_BITMAP* bmp = tileSet[347]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING3) {

                ALLEGRO_BITMAP* bmp = tileSet[348]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING4) {

                ALLEGRO_BITMAP* bmp = tileSet[349]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING5) {

                ALLEGRO_BITMAP* bmp = tileSet[350]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING6) {

                ALLEGRO_BITMAP* bmp = tileSet[351]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING7) {

                ALLEGRO_BITMAP* bmp = tileSet[352]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING8) {

                ALLEGRO_BITMAP* bmp = tileSet[353]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING9) {

                ALLEGRO_BITMAP* bmp = tileSet[354]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING10) {

                ALLEGRO_BITMAP* bmp = tileSet[355]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING11) {

                ALLEGRO_BITMAP* bmp = tileSet[356]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING12) {

                ALLEGRO_BITMAP* bmp = tileSet[357]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING13) {

                ALLEGRO_BITMAP* bmp = tileSet[358]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING14) {

                ALLEGRO_BITMAP* bmp = tileSet[359]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING15) {

                ALLEGRO_BITMAP* bmp = tileSet[360]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING16) {

                ALLEGRO_BITMAP* bmp = tileSet[361]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING17) {

                ALLEGRO_BITMAP* bmp = tileSet[362]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::PARKING18) {

                ALLEGRO_BITMAP* bmp = tileSet[363]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }

            else if (type == BlockType::CLUB1) {

                ALLEGRO_BITMAP* bmp = tileSet[364]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB2) {

                ALLEGRO_BITMAP* bmp = tileSet[365]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB3) {

                ALLEGRO_BITMAP* bmp = tileSet[366]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB4) {

                ALLEGRO_BITMAP* bmp = tileSet[367]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB5) {

                ALLEGRO_BITMAP* bmp = tileSet[368]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB6) {

                ALLEGRO_BITMAP* bmp = tileSet[369]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB7) {

                ALLEGRO_BITMAP* bmp = tileSet[370]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB8) {

                ALLEGRO_BITMAP* bmp = tileSet[371]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB9) {

                ALLEGRO_BITMAP* bmp = tileSet[372]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB10) {

                ALLEGRO_BITMAP* bmp = tileSet[373]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB11) {

                ALLEGRO_BITMAP* bmp = tileSet[374]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB12) {

                ALLEGRO_BITMAP* bmp = tileSet[375]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB13) {

                ALLEGRO_BITMAP* bmp = tileSet[376]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB14) {

                ALLEGRO_BITMAP* bmp = tileSet[377]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB15) {

                ALLEGRO_BITMAP* bmp = tileSet[378]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB16) {

                ALLEGRO_BITMAP* bmp = tileSet[379]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB17) {

                ALLEGRO_BITMAP* bmp = tileSet[380]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB18) {

                ALLEGRO_BITMAP* bmp = tileSet[381]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB19) {

                ALLEGRO_BITMAP* bmp = tileSet[382]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB20) {

                ALLEGRO_BITMAP* bmp = tileSet[383]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB21) {

                ALLEGRO_BITMAP* bmp = tileSet[384]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB22) {

                ALLEGRO_BITMAP* bmp = tileSet[385]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB23) {

                ALLEGRO_BITMAP* bmp = tileSet[386]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB24) {

                ALLEGRO_BITMAP* bmp = tileSet[387]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB25) {

                ALLEGRO_BITMAP* bmp = tileSet[388]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB26) {

                ALLEGRO_BITMAP* bmp = tileSet[389]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB27) {

                ALLEGRO_BITMAP* bmp = tileSet[390]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB28) {

                ALLEGRO_BITMAP* bmp = tileSet[391]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB29) {

                ALLEGRO_BITMAP* bmp = tileSet[392]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB30) {

                ALLEGRO_BITMAP* bmp = tileSet[393]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB31) {

                ALLEGRO_BITMAP* bmp = tileSet[394]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CLUB32) {

                ALLEGRO_BITMAP* bmp = tileSet[395]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            

            else if (type == BlockType::SHOP1) {

                ALLEGRO_BITMAP* bmp = tileSet[396]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP2) {

                ALLEGRO_BITMAP* bmp = tileSet[397]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP3) {

                ALLEGRO_BITMAP* bmp = tileSet[398]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP4) {

                ALLEGRO_BITMAP* bmp = tileSet[399]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP5) {

                ALLEGRO_BITMAP* bmp = tileSet[400]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP6) {

                ALLEGRO_BITMAP* bmp = tileSet[401]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP7) {

                ALLEGRO_BITMAP* bmp = tileSet[402]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP8) {

                ALLEGRO_BITMAP* bmp = tileSet[403]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::SHOP9) {

                ALLEGRO_BITMAP* bmp = tileSet[404]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            /*else if (type >= BlockType::SHOP2 && type <= BlockType::SHOP9) {

                int index = static_cast<int>(type) - static_cast<int>(BlockType::SHOP2) + 396;
                ALLEGRO_BITMAP* bmp = tileSet[index]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }*/
            else if (type == BlockType::REST1) {

                ALLEGRO_BITMAP* bmp = tileSet[405]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST2) {

                ALLEGRO_BITMAP* bmp = tileSet[406]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST3) {

                ALLEGRO_BITMAP* bmp = tileSet[407]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST4) {

                ALLEGRO_BITMAP* bmp = tileSet[408]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST5) {

                ALLEGRO_BITMAP* bmp = tileSet[409]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST6) {

                ALLEGRO_BITMAP* bmp = tileSet[410]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST7) {

                ALLEGRO_BITMAP* bmp = tileSet[411]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST8) {

                ALLEGRO_BITMAP* bmp = tileSet[412]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST9) {

                ALLEGRO_BITMAP* bmp = tileSet[413]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST10) {

                ALLEGRO_BITMAP* bmp = tileSet[414]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST11) {

                ALLEGRO_BITMAP* bmp = tileSet[415]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::REST12) {

                ALLEGRO_BITMAP* bmp = tileSet[416]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }

            else if (type == BlockType::CASTLE1) {

                ALLEGRO_BITMAP* bmp = tileSet[417]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE2) {

                ALLEGRO_BITMAP* bmp = tileSet[418]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE3) {

                ALLEGRO_BITMAP* bmp = tileSet[419]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE4) {

                ALLEGRO_BITMAP* bmp = tileSet[420]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE5) {

                ALLEGRO_BITMAP* bmp = tileSet[421]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE6) {

                ALLEGRO_BITMAP* bmp = tileSet[422]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE7) {

                ALLEGRO_BITMAP* bmp = tileSet[423]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE8) {

                ALLEGRO_BITMAP* bmp = tileSet[424]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE9) {

                ALLEGRO_BITMAP* bmp = tileSet[425]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE10) {

                ALLEGRO_BITMAP* bmp = tileSet[426]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE11) {

                ALLEGRO_BITMAP* bmp = tileSet[427]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE12) {

                ALLEGRO_BITMAP* bmp = tileSet[428]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE13) {

                ALLEGRO_BITMAP* bmp = tileSet[429]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE14) {

                ALLEGRO_BITMAP* bmp = tileSet[430]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE15) {

                ALLEGRO_BITMAP* bmp = tileSet[431]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE16) {

                ALLEGRO_BITMAP* bmp = tileSet[432]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE17) {

                ALLEGRO_BITMAP* bmp = tileSet[433]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE18) {

                ALLEGRO_BITMAP* bmp = tileSet[434]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE19) {

                ALLEGRO_BITMAP* bmp = tileSet[435]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE20) {

                ALLEGRO_BITMAP* bmp = tileSet[436]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE21) {

                ALLEGRO_BITMAP* bmp = tileSet[437]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE22) {

                ALLEGRO_BITMAP* bmp = tileSet[438]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE23) {

                ALLEGRO_BITMAP* bmp = tileSet[439]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE24) {

                ALLEGRO_BITMAP* bmp = tileSet[440]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE25) {

                ALLEGRO_BITMAP* bmp = tileSet[441]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE26) {

                ALLEGRO_BITMAP* bmp = tileSet[442]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE27) {

                ALLEGRO_BITMAP* bmp = tileSet[443]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE28) {

                ALLEGRO_BITMAP* bmp = tileSet[444]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE29) {

                ALLEGRO_BITMAP* bmp = tileSet[445]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE30) {

                ALLEGRO_BITMAP* bmp = tileSet[446]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE31) {

                ALLEGRO_BITMAP* bmp = tileSet[447]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE32) {

                ALLEGRO_BITMAP* bmp = tileSet[448]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE33) {

                ALLEGRO_BITMAP* bmp = tileSet[449]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE34) {

                ALLEGRO_BITMAP* bmp = tileSet[450]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE35) {

                ALLEGRO_BITMAP* bmp = tileSet[451]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE36) {

                ALLEGRO_BITMAP* bmp = tileSet[452]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE37) {

                ALLEGRO_BITMAP* bmp = tileSet[453]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE38) {

                ALLEGRO_BITMAP* bmp = tileSet[454]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE39) {

                ALLEGRO_BITMAP* bmp = tileSet[455]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE40) {

                ALLEGRO_BITMAP* bmp = tileSet[456]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE41) {

                ALLEGRO_BITMAP* bmp = tileSet[457]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE42) {

                ALLEGRO_BITMAP* bmp = tileSet[458]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE43) {

                ALLEGRO_BITMAP* bmp = tileSet[459]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE44) {

                ALLEGRO_BITMAP* bmp = tileSet[460]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE45) {

                ALLEGRO_BITMAP* bmp = tileSet[461]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE46) {

                ALLEGRO_BITMAP* bmp = tileSet[462]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE47) {

                ALLEGRO_BITMAP* bmp = tileSet[463]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::CASTLE48) {

                ALLEGRO_BITMAP* bmp = tileSet[464]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }

            else if (type == BlockType::COFFEE1) {

                ALLEGRO_BITMAP* bmp = tileSet[466]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE2) {

                ALLEGRO_BITMAP* bmp = tileSet[467]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE3) {

                ALLEGRO_BITMAP* bmp = tileSet[468]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE4) {

                ALLEGRO_BITMAP* bmp = tileSet[469]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE5) {

                ALLEGRO_BITMAP* bmp = tileSet[470]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE6) {

                ALLEGRO_BITMAP* bmp = tileSet[471]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE7) {

                ALLEGRO_BITMAP* bmp = tileSet[472]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE8) {

                ALLEGRO_BITMAP* bmp = tileSet[473]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE9) {

                ALLEGRO_BITMAP* bmp = tileSet[474]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE10) {

                ALLEGRO_BITMAP* bmp = tileSet[475]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE11) {

                ALLEGRO_BITMAP* bmp = tileSet[476]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE12) {

                ALLEGRO_BITMAP* bmp = tileSet[477]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE13) {

                ALLEGRO_BITMAP* bmp = tileSet[478]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE14) {

                ALLEGRO_BITMAP* bmp = tileSet[479]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE15) {

                ALLEGRO_BITMAP* bmp = tileSet[480]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE16) {

                ALLEGRO_BITMAP* bmp = tileSet[481]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE17) {

                ALLEGRO_BITMAP* bmp = tileSet[482]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE18) {

                ALLEGRO_BITMAP* bmp = tileSet[483]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE19) {

                ALLEGRO_BITMAP* bmp = tileSet[484]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE20) {

                ALLEGRO_BITMAP* bmp = tileSet[485]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE21) {

                ALLEGRO_BITMAP* bmp = tileSet[486]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE22) {

                ALLEGRO_BITMAP* bmp = tileSet[487]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE23) {

                ALLEGRO_BITMAP* bmp = tileSet[488]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::COFFEE24) {

                ALLEGRO_BITMAP* bmp = tileSet[489]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }

            else if (type == BlockType::GRASS1) {

                ALLEGRO_BITMAP* bmp = tileSet[490]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS2) {

                ALLEGRO_BITMAP* bmp = tileSet[491]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS3) {

                ALLEGRO_BITMAP* bmp = tileSet[492]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS4) {

                ALLEGRO_BITMAP* bmp = tileSet[493]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS5) {

                ALLEGRO_BITMAP* bmp = tileSet[494]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS6) {

                ALLEGRO_BITMAP* bmp = tileSet[495]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS7) {

                ALLEGRO_BITMAP* bmp = tileSet[496]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS8) {

                ALLEGRO_BITMAP* bmp = tileSet[497]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS9) {

                ALLEGRO_BITMAP* bmp = tileSet[498]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS10) {

                ALLEGRO_BITMAP* bmp = tileSet[499]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS11) {

                ALLEGRO_BITMAP* bmp = tileSet[500]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS12) {

                ALLEGRO_BITMAP* bmp = tileSet[501]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS13) {

                ALLEGRO_BITMAP* bmp = tileSet[502]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS14) {

                ALLEGRO_BITMAP* bmp = tileSet[503]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS15) {

                ALLEGRO_BITMAP* bmp = tileSet[504]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS16) {

                ALLEGRO_BITMAP* bmp = tileSet[505]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS17) {

                ALLEGRO_BITMAP* bmp = tileSet[506]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS18) {

                ALLEGRO_BITMAP* bmp = tileSet[507]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS19) {

                ALLEGRO_BITMAP* bmp = tileSet[508]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS20) {

                ALLEGRO_BITMAP* bmp = tileSet[509]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS21) {

                ALLEGRO_BITMAP* bmp = tileSet[510]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS22) {

                ALLEGRO_BITMAP* bmp = tileSet[511]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS23) {

                ALLEGRO_BITMAP* bmp = tileSet[512]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::GRASS24) {

                ALLEGRO_BITMAP* bmp = tileSet[513]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            

        }
    }
}

void Map::update(float deltaTime) {
    // 更新硬幣動畫、硬幣狀態等
    // 例如判斷玩家是否在硬幣上，更新 totalCoins 等
    scene = getPlayScene();
    if (!scene) return;

    int playerX = static_cast<int>(scene->GetPlayer()->Position.x) / tileSize;
    int playerY = static_cast<int>(scene->GetPlayer()->Position.y) / tileSize;

    if (playerX < 0 || playerY < 0 || playerX >= cols || playerY >= rows) return;

    BlockType tile = mapGrid[playerY][playerX];

    /*if (tile == BlockType::HOUSE) {
        // 玩家走進房子，切換到任務場景
        Engine::GameEngine::GetInstance().ChangeScene("quiz");
    }*/

    std::pair<int, int> currentTile = {playerY, playerX};
    if(tile == BlockType::CSBUILDING46){
        if (triggeredQuizzes.find(currentTile) == triggeredQuizzes.end() && !WaitToChangeScene) {
            //triggeredQuizzes.insert(currentTile);
            //Engine::GameEngine::GetInstance().ChangeScene("quiz");
            WaitToChangeScene = true;
            quizTriggerTimer = 1.0f;
        }
        if (WaitToChangeScene) {
            quizTriggerTimer -= deltaTime;
            if (quizTriggerTimer <= 0.0f) {
                WaitToChangeScene = false;
                triggeredQuizzes.insert(currentTile);
                Engine::GameEngine::GetInstance().ChangeScene("quiz");
            }
        }
    }
    else if(tile == BlockType::CLUB28){
        if (triggeredQuizzes.find(currentTile) == triggeredQuizzes.end() && !WaitToChangeScene) {
            //triggeredQuizzes.insert(currentTile);
            //Engine::GameEngine::GetInstance().ChangeScene("quiz");
            WaitToChangeScene = true;
            quizTriggerTimer = 1.0f;
        }
        if (WaitToChangeScene) {
            quizTriggerTimer -= deltaTime;
            if (quizTriggerTimer <= 0.0f) {
                WaitToChangeScene = false;
                triggeredQuizzes.insert(currentTile);
                Engine::GameEngine::GetInstance().ChangeScene("rhythm");
            }
        }
    }
    
    
}

bool Map::isWalkable(BlockType block) const {
    switch (block) {
        case BlockType::FLOOR: return true;

        case BlockType::TENNIS1: return true;
        case BlockType::TENNIS6: return true;
        case BlockType::TENNIS7: return true;
        case BlockType::TENNIS12: return true;
        case BlockType::TENNIS13: return true;
        case BlockType::TENNIS18: return true;
        case BlockType::TENNIS19: return true;
        case BlockType::TENNIS24: return true;
        case BlockType::TENNIS25: return true;
        case BlockType::TENNIS30: return true;
        case BlockType::TENNIS31: return true;
        case BlockType::TENNIS36: return true;
        case BlockType::TENNIS37: return true;
        case BlockType::TENNIS42: return true;

        case BlockType::CASTLE1: return true;
        case BlockType::CASTLE2: return true;
        case BlockType::CASTLE3: return true;
        case BlockType::CASTLE4: return true;
        case BlockType::CASTLE5: return true;
        case BlockType::CASTLE6: return true;
        case BlockType::CASTLE7: return true;
        case BlockType::CASTLE11: return true;
        case BlockType::CASTLE12: return true;
        case BlockType::CASTLE39: return true;
        case BlockType::CASTLE43: return true;
        case BlockType::CASTLE44: return true;
        case BlockType::CASTLE45: return true;
        case BlockType::CASTLE46: return true;
        case BlockType::CASTLE47: return true;
        case BlockType::CASTLE48: return true;

        case BlockType::CLUB1: return true;
        case BlockType::CLUB2: return true;
        case BlockType::CLUB3: return true;
        case BlockType::CLUB7: return true;
        case BlockType::CLUB8: return true;
        case BlockType::CLUB9: return true;
        case BlockType::CLUB16: return true;
        case BlockType::CLUB17: return true;
        case BlockType::CLUB24: return true;
        case BlockType::CLUB25: return true;
        case BlockType::CLUB28: return true;
        case BlockType::CLUB32: return true;

        case BlockType::CODE1: return true;
        case BlockType::CODE2: return true;
        case BlockType::CODE3: return true;
        case BlockType::CODE4: return true;
        case BlockType::CODE5: return true;
        case BlockType::CODE26: return true;
        case BlockType::CODE27: return true;
        case BlockType::CODE28: return true;
        case BlockType::CODE29: return true;
        case BlockType::CODE30: return true;

        case BlockType::COFFEE1: return true;
        case BlockType::COFFEE3: return true;
        case BlockType::COFFEE4: return true;
        case BlockType::COFFEE21: return true;
        case BlockType::COFFEE22: return true;
        case BlockType::COFFEE23: return true;
        case BlockType::COFFEE24: return true;

        //case BlockType::ROCKROAD: return true;
        case BlockType::CSBUILDING46: return true;

        case BlockType::LAKE1: return true;
        case BlockType::LAKE6: return true;
        case BlockType::LAKE11: return true;
        case BlockType::LAKE16: return true;
        case BlockType::LAKE21: return true;

        case BlockType::LIBRARY1: return true;
        case BlockType::LIBRARY2: return true;
        case BlockType::LIBRARY3: return true;
        case BlockType::LIBRARY4: return true;
        case BlockType::LIBRARY5: return true;
        case BlockType::LIBRARY6: return true;
        case BlockType::LIBRARY7: return true;
        case BlockType::LIBRARY8: return true;
        case BlockType::LIBRARY17: return true;
        case BlockType::LIBRARY32: return true;
        case BlockType::LIBRARY33: return true;
        case BlockType::LIBRARY37: return true;
        case BlockType::LIBRARY40: return true;
        case BlockType::LIBRARY41: return true;
        case BlockType::LIBRARY42: return true;
        case BlockType::LIBRARY44: return true;
        case BlockType::LIBRARY45: return true;
        case BlockType::LIBRARY48: return true;

        case BlockType::GROUND1: return true;
        case BlockType::GROUND6: return true;
        case BlockType::GROUND12: return true;
        case BlockType::GROUND13: return true;
        case BlockType::GROUND18: return true;
        case BlockType::GROUND24: return true;

        case BlockType::POOL1: return true;
        case BlockType::POOL2: return true;
        case BlockType::POOL3: return true;
        case BlockType::POOL4: return true;
        case BlockType::POOL5: return true;
        case BlockType::POOL10: return true;
        case BlockType::POOL25: return true;
        case BlockType::POOL20: return true;
        case BlockType::POOL21: return true;
        case BlockType::POOL22: return true;
        case BlockType::POOL23: return true;
        case BlockType::POOL24: return true;

        case BlockType::QINLAKE1: return true;
        case BlockType::QINLAKE2: return true;
        case BlockType::QINLAKE3: return true;
        case BlockType::QINLAKE7: return true;
        case BlockType::QINLAKE8: return true;
        case BlockType::QINLAKE9: return true;
        case BlockType::QINLAKE10: return true;
        case BlockType::QINLAKE12: return true;
        case BlockType::QINLAKE13: return true;
        case BlockType::QINLAKE15: return true;
        case BlockType::QINLAKE16: return true;
        case BlockType::QINLAKE17: return true;
        //case BlockType::QINLAKE21: return true;
        case BlockType::QINLAKE22: return true;
        case BlockType::QINLAKE24: return true;
        case BlockType::QINLAKE25: return true;
        case BlockType::QINLAKE30: return true;
        case BlockType::QINLAKE31: return true;
        case BlockType::QINLAKE32: return true;
        case BlockType::QINLAKE33: return true;
        case BlockType::QINLAKE34: return true;
        case BlockType::QINLAKE37: return true;
        case BlockType::QINLAKE38: return true;
        case BlockType::QINLAKE39: return true;
        case BlockType::QINLAKE40: return true;

        case BlockType::REST1: return true;
        case BlockType::REST4: return true;
        case BlockType::REST5: return true;
        case BlockType::REST8: return true;
        case BlockType::REST9: return true;
        case BlockType::REST10: return true;
        case BlockType::REST11: return true;
        case BlockType::REST12: return true;

        case BlockType::SHOP7: return true;
        case BlockType::SHOP8: return true;
        case BlockType::SHOP9: return true;
        
        case BlockType::COIN: return true; // 可走
        // 其他判斷
        default: return false;
    }
}

Engine::Point Map::WorldToTile(const Engine::Point& pos){
    return Engine::Point(static_cast<int>(pos.x) / tileSize, static_cast<int>(pos.y) / tileSize);
}

BlockType Map::GetBlock(const Engine::Point& tilePos) {
    // 確保 tilePos 在合法範圍內
    int x = static_cast<int>(tilePos.x);
    int y = static_cast<int>(tilePos.y);

    if (x >= 0 && x < PlayScene::MapWidth && y >= 0 && y < PlayScene::MapHeight) {
        return tiles[y][x]; // y 是 row x 是 column
    }
    // 超出邊界
    return BlockType::NOTHING;
}

int Map::GetWidth() const{
    return cols;
}
int Map::GetHeight() const{
    return rows;
}

const std::vector<std::vector<BlockType>>& Map::GetGrid() const {
    return mapGrid;
}

