#ifndef MAJ_YAKU_H
#define MAJ_YAKU_H

#include "pointers.h"

namespace FZMAJ_NS {

const char YAKU_NAME[46][25] = {

    {"Reach           "},  // 1. ri-chi
    {"Ippatsu         "},  // 2.
    {"Menchin Tsumo   "},  // 3. menzenchin tsumohou
    {"Tan Yao         "},  // 4. tanyaochou
    {"Pinfu           "},  // 5
    {"I-pei kou       "},  // 6
    {"Yakuhai Bafuu   "},  // 7
    {"Yakuhai Jifuu   "},  // 8
    {"Yakuhai Sangen  "},  // 9
    {"Rinshan Kaihou  "},  // 10
    {"Chan Kan        "},  // 11
    {"Haitei Raoyue   "},  // 12
    {"Houtei Raoyuu   "},  // 13
    {"Dora            "},  // 14
    {"Ura Dora        "},  // 15
    {"Aka Dora        "},  // 16

    {"SanShoku Doujun "},  // 17
    {"Ikki Tsukan     "},  // 18
    {"Hon Chantai     "},  // 19
    {"Chii Toitsu     "},  // 20
    {"Toitoi          "},  // 21
    {"San Ankou       "},  // 22
    {"Hon Rou Tou     "},  // 23
    {"Sanshoku Doukou "},  // 24
    {"San Kantsu      "},  // 25
    {"Shou Sangen     "},  // 26
    {"Double Riichi   "},  // 27

    {"Hon I-Sou       "},  // 28
    {"Jonchan         "},  // 29
    {"Ryanpei kou     "},  // 30

    {"Chin I-Sou      "},  // 31

    {"Kokushi Musou   "},  // 32
    {"Kokushi 13 Machi"},  // 33
    {"Su Ankou        "},  // 34
    {"Su Ankou Tanki  "},  // 35
    {"Da Sangen       "},  // 36
    {"Tsu I-Sou       "},  // 37
    {"Shou Su Shi     "},  // 38
    {"Da Su Shi       "},  // 39
    {"Ryuu I-Sou      "},  // 40
    {"Chin Rou Tou    "},  // 41
    {"Su Kantsu       "},  // 42
    {"Chuuren Boutou  "},  // 43
    {"Jon Chuuren     "},  // 44
    {"Ten Hou         "},  // 45
    {"Chi Hou         "}   // 46
};

enum YAKU_SHURUI {
    YAKU_REACH=0,                       // 0
    YAKU_IPPATSU,                       // 1    
    YAKU_MENTSUMO,                      // 2
    YAKU_TANYAO,                        // 3
    YAKU_PINFU,                         // 4
    YAKU_IPPEI,                         // 5
    YAKU_YAKUHAI_BAFUU,                 // 6
    YAKU_YAKUHAI_JIFUU,                 // 7
    YAKU_YAKUHAI_SANGEN,                // 8
    YAKU_RINSHAN,                       // 9
    YAKU_CHANKAN,                       // 10
    YAKU_HAITEI,                        // 11
    YAKU_HOUTEI,                        // 12
    YAKU_DORA,                          // 13
    YAKU_URA,                           // 14
    YAKU_AKA,                           // 15

    YAKU_SANSHOKU,                      // 16
    YAKU_IKKI,                          // 17
    YAKU_HONCHAN,                       // 18
    YAKU_CHIITOI,                       // 19
    YAKU_TOITOI,                        // 20
    YAKU_SANANKO,                       // 21
    YAKU_HONROU,                        // 22
    YAKU_TONKO,                         // 23
    YAKU_SANKANTSU,                     // 24
    YAKU_SHOUSANGEN,                    // 25
    YAKU_WREACH,                        // 26

    YAKU_HONITSU,                       // 27
    YAKU_JONCHAN,                       // 28
    YAKU_RYANPEI,                       // 29

    YAKU_CHINITSU,                      // 30

    YAKU_KOKUSHI,                       // 31
    YAKU_KOKUSHI_13,                    // 32
    YAKU_SUANKO,                        // 33
    YAKU_SUANKO_TANKI,                  // 34
    YAKU_DASANGEN,                      // 35
    YAKU_TSUIISOU,                      // 36
    YAKU_SHOUSUSHI,                     // 37
    YAKU_DASUSHI,                       // 38
    YAKU_RYOUIISOU,                     // 39
    YAKU_CHINROU,                       // 40
    YAKU_SUKANTSU,                      // 41
    YAKU_CHUUREN,                       // 42
    YAKU_JONCHUUREN,                    // 43
    YAKU_TENHOU,                        // 44
    YAKU_CHIHOU                         // 45
};

class Yaku : protected Pointers {
  public:
    Yaku(class FZMAJ *);
    ~Yaku();
    int count_yaku(Bakyou*, Pattern &);
  protected:

    Bakyou * bak;
    Pattern * pat;

    int fan;
    int fu;
    int yaku[46];
    int yaku_fan[46];
    int score;
    int fan_nodora;

    // 1 fan

    int is_reach();
    int is_ippatsu();
    int is_mentsumo();
    int is_tanyao();
    int is_pinfu();
    int is_ippei();
    int is_yakuhai_bafuu();
    int is_yakuhai_jifuu();
    int is_yakuhai_sangen();
    int is_chankan();
    int is_rinshan();
    int is_haitei();
    int is_houtei();

    // 2 fan

    int is_sanshoku();
    int is_ikki();
    int is_honchan();
    int is_chiitoi();
    int is_toitoi();
    int is_sananko();
    int is_honrou();
    int is_tonko();
    int is_sankantsu();
    int is_shousangen();
    int is_wreach();

    // 3 fan
    
    int is_honitsu();
    int is_jonchan();
    int is_ryanpei();

    // 6 fan
    
    int is_chinitsu();

    // 13 fan

    int is_kokushi();
    int is_kokushi_13();
    int is_suanko();
    int is_suanko_tanki();
    int is_dasangen();
    int is_tsuiisou();
    int is_shousushi();
    int is_dasushi();
    int is_ryouiisou();
    int is_chinrou();
    int is_sukantsu();
    int is_chouren();
    int is_jonchouren();
    int is_tenhou();
    int is_chihou();

    int check_peikou();
    int check_chanta();
};


}


#endif
