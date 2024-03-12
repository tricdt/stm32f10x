/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Spell.c
** Descriptions:            Æ´ÒôÊäÈë·¨
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Ya Dan
** Created date:            2011-1-18
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Mem.h"	

/* Private typedef -----------------------------------------------------------*/
/* Æ´Òô×éºÏµÄºº×Ö×Ö¿â */
/* Æ´Òô¼ìË÷µÄ½á¹¹Ìå */
struct PinYinPCB
{
   const char *PYSerList;  		 /* Æ´Òô¼ìË÷×Ö·û */
   const char *PYRankOneList;  	 /* ÒÔËù¶¨ÒåµÄÆ´Òô×éºÏµÄºº×Ö×Ö¿âµÄÖ¸Õë */
};

/* Private variables ---------------------------------------------------------*/
const char PY_MB_a[]     ={"°¢°¡"};
const char PY_MB_ai[]    ={"°¥°§°¦°£°¤°¨°©°«°ª°¬°®°¯°­"};
const char PY_MB_an[]    ={"°²°±°°°³°¶°´°¸°·°µ"};
const char PY_MB_ang[]   ={"°¹°º°»"};
const char PY_MB_ao[]    ={"°¼°½°¾°¿°À°Á°Â°Ä°Ã"};
const char PY_MB_ba[]    ={"°Ë°Í°È°Ç°É°Å°Ì°Æ°Ê°Î°Ï°Ñ°Ğ°Ó°Ö°Õ°Ô"};
const char PY_MB_bai[]   ={"°×°Ù°Û°Ø°Ú°Ü°İ°Ş"};
const char PY_MB_ban[]   ={"°â°à°ã°ä°ß°á°å°æ°ì°ë°é°ç°è°í°ê"};
const char PY_MB_bang[]  ={"°î°ï°ğ°ó°ñ°ò°ö°ø°ô°ù°õ°÷"};
const char PY_MB_bao[]   ={"°ü°ú°û°ı±¢±¦±¥±£±¤±¨±§±ª±«±©±¬°ş±¡ÆÙ"};
const char PY_MB_bei[]   ={"±°±­±¯±®±±±´±·±¸±³±µ±¶±»±¹±º±²"};
const char PY_MB_ben[]   ={"±¼±¾±½±¿º»"};
const char PY_MB_beng[]  ={"±À±Á±Â±Ã±Å±Ä"};
const char PY_MB_bi[]    ={"±Æ±Ç±È±Ë±Ê±É±Ò±Ø±Ï±Õ±Ó±Ñ±İ±Ğ±Ö±Ô±Í±×±Ì±Î±Ú±Ü±Û"};
const char PY_MB_bian[]  ={"±ß±à±Ş±á±â±å±ã±ä±é±æ±ç±è"};
const char PY_MB_biao[]  ={"±ë±ê±ì±í"};
const char PY_MB_bie[]   ={"±ï±î±ğ±ñ"};
const char PY_MB_bin[]   ={"±ö±ò±ó±õ±ô±÷"};
const char PY_MB_bing[]  ={"±ù±ø±û±ü±ú±ş±ı²¢²¡"};
const char PY_MB_bo[]    ={"²¦²¨²£²§²±²¤²¥²®²µ²¯²´²ª²¬²°²©²³²«²­²²²·"};
const char PY_MB_bu[]    ={"²¹²¸²¶²»²¼²½²À²¿²º²¾"};
const char PY_MB_ca[]    ={"²Á"};
const char PY_MB_cai[]   ={"²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
const char PY_MB_can[]   ={"²Î²Í²Ğ²Ï²Ñ²Ò²Ó"};
const char PY_MB_cang[]  ={"²Ö²×²Ô²Õ²Ø"};
const char PY_MB_cao[]   ={"²Ù²Ú²Ü²Û²İ"};
const char PY_MB_ce[]    ={"²á²à²Ş²â²ß"};
const char PY_MB_ceng[]  ={"²ã²äÔø"};
const char PY_MB_cha[]   ={"²æ²å²é²ç²è²ë²ì²ê²í²ï²îÉ²"};
const char PY_MB_chai[]  ={"²ğ²ñ²ò"};
const char PY_MB_chan[]  ={"²ô²ó²÷²ö²ø²õ²ú²ù²û²ü"};
const char PY_MB_chang[] ={"²ı²ş³¦³¢³¥³£³§³¡³¨³©³«³ª"};
const char PY_MB_chao[]  ={"³­³®³¬³²³¯³°³±³³³´´Â"};
const char PY_MB_che[]   ={"³µ³¶³¹³¸³·³º"};
const char PY_MB_chen[]  ={"³»³¾³¼³À³Á³½³Â³¿³Ä³Ã"};
const char PY_MB_cheng[] ={"³Æ³Å³É³Ê³Ğ³Ï³Ç³Ë³Í³Ì³Î³È³Ñ³Ò³Ó"};
const char PY_MB_chi[]   ={"³Ô³Õ³Ú³Ø³Û³Ù³Ö³ß³Ş³İ³Ü³â³à³ã³á"};
const char PY_MB_chong[] ={"³ä³å³æ³ç³è"};
const char PY_MB_chou[]  ={"³é³ğ³ñ³ë³î³í³ï³ê³ì³ó³ò³ô"};
const char PY_MB_chu[]   ={"³ö³õ³ı³ø³ü³ú³û³÷³ù´¡´¢³ş´¦´¤´¥´£Ğó"};
const char PY_MB_chuai[] ={"´§"};
const char PY_MB_chuan[] ={"´¨´©´«´¬´ª´­´®"};
const char PY_MB_chuang[]={"´³´¯´°´²´´"};
const char PY_MB_chui[]  ={"´µ´¶´¹´·´¸"};
const char PY_MB_chun[]  ={"´º´»´¿´½´¾´¼´À"};
const char PY_MB_chuo[]  ={"´Á"};
const char PY_MB_ci[]    ={"´Ã´Ê´Ä´É´È´Ç´Å´Æ´Ë´Î´Ì´Í"};
const char PY_MB_cong[]  ={"´Ñ´Ó´Ò´Ğ´Ï´Ô"};
const char PY_MB_cou[]   ={"´Õ"};
const char PY_MB_cu[]    ={"´Ö´Ù´×´Ø"};
const char PY_MB_cuan[]  ={"´Ú´Ü´Û"};
const char PY_MB_cui[]   ={"´Ş´ß´İ´à´ã´á´â´ä"};
const char PY_MB_cun[]   ={"´å´æ´ç"};
const char PY_MB_cuo[]   ={"´ê´è´é´ì´ë´í"};
const char PY_MB_da[]    ={"´î´ï´ğ´ñ´ò´ó"};
const char PY_MB_dai[]   ={"´ô´õ´ö´ú´ø´ıµ¡´ù´û´ü´ş´÷"};
const char PY_MB_dan[]   ={"µ¤µ¥µ£µ¢µ¦µ¨µ§µ©µ«µ®µ¯µ¬µ­µ°µª"};
const char PY_MB_dang[]  ={"µ±µ²µ³µ´µµ"};
const char PY_MB_dao[]   ={"µ¶µ¼µºµ¹µ·µ»µ¸µ½µ¿µÁµÀµ¾"};
const char PY_MB_de[]    ={"µÃµÂµÄ"};
const char PY_MB_deng[]  ={"µÆµÇµÅµÈµËµÊµÉ"};
const char PY_MB_di[]    ={"µÍµÌµÎµÒµÏµĞµÓµÑµÕµ×µÖµØµÜµÛµİµÚµŞµÙ"};
const char PY_MB_dian[]  ={"µàµáµßµäµãµâµçµèµéµêµæµëµíµìµîµå"};
const char PY_MB_diao[]  ={"µóµğµòµïµñµõµöµô"};
const char PY_MB_die[]   ={"µùµøµüµıµşµúµû"};
const char PY_MB_ding[]  ={"¶¡¶£¶¢¶¤¶¥¶¦¶©¶¨¶§"};
const char PY_MB_diu[]   ={"¶ª"};
const char PY_MB_dong[]  ={"¶«¶¬¶­¶®¶¯¶³¶±¶²¶°¶´"};
const char PY_MB_dou[]   ={"¶¼¶µ¶·¶¶¶¸¶¹¶º¶»"};
const char PY_MB_du[]    ={"¶½¶¾¶Á¶¿¶À¶Â¶Ä¶Ã¶Ê¶Å¶Ç¶È¶É¶Æ"};
const char PY_MB_duan[]  ={"¶Ë¶Ì¶Î¶Ï¶Ğ¶Í"};
const char PY_MB_dui[]   ={"¶Ñ¶Ó¶Ô¶Ò"};
const char PY_MB_dun[]   ={"¶Ö¶Ø¶Õ¶×¶Ü¶Û¶Ù¶İ"};
const char PY_MB_duo[]   ={"¶à¶ß¶á¶Ş¶ä¶â¶ã¶ç¶é¶æ¶è¶å"};
const char PY_MB_e[]     ={"¶ï¶í¶ğ¶ë¶ì¶ê¶î¶ò¶ó¶ñ¶ö¶õ¶ô"};
const char PY_MB_en[]    ={"¶÷"};
const char PY_MB_er[]    ={"¶ù¶ø¶û¶ú¶ı¶ü¶ş·¡"};
const char PY_MB_fa[]    ={"·¢·¦·¥·£·§·¤·¨·©"};
const char PY_MB_fan[]   ={"·«·¬·­·ª·²·¯·°·³·®·±·´·µ·¸·º·¹·¶··"};
const char PY_MB_fang[]  ={"·½·»·¼·À·Á·¿·¾·Â·Ã·Ä·Å"};
const char PY_MB_fei[]   ={"·É·Ç·È·Æ·Ê·Ë·Ì·Í·Ï·Ğ·Î·Ñ"};
const char PY_MB_fen[]   ={"·Ö·Ô·×·Ò·Õ·Ó·Ø·Ú·Ù·Û·İ·Ü·Ş·ß·à"};
const char PY_MB_feng[]  ={"·á·ç·ã·â·è·å·é·æ·ä·ë·ê·ì·í·ï·î"};
const char PY_MB_fo[]    ={"·ğ"};
const char PY_MB_fou[]   ={"·ñ"};
const char PY_MB_fu[]    ={"·ò·ô·õ·ó¸¥·ü·ö·÷·ş·ı·ú¸¡¸¢·û¸¤·ù¸£·ø¸§¸¦¸®¸«¸©¸ª¸¨¸­¸¯¸¸¸¼¸¶¸¾¸º¸½¸À¸·¸´¸°¸±¸µ¸»¸³¸¿¸¹¸²"};
const char PY_MB_ga[]    ={"¸Â¸Á"};
const char PY_MB_gai[]   ={"¸Ã¸Ä¸Æ¸Ç¸È¸Å"};
const char PY_MB_gan[]   ={"¸É¸Ê¸Ë¸Î¸Ì¸Í¸Ñ¸Ï¸Ò¸Ğ¸Ó"};
const char PY_MB_gang[]  ={"¸Ô¸Õ¸Ú¸Ù¸Ø¸×¸Ö¸Û¸Ü"};
const char PY_MB_gao[]   ={"¸Ş¸á¸ß¸à¸İ¸â¸ã¸å¸ä¸æ"};
const char PY_MB_ge[]    ={"¸ê¸í¸ç¸ì¸ë¸î¸é¸è¸ó¸ï¸ñ¸ğ¸ô¸ö¸÷¸õ¿©"};
const char PY_MB_gei[]   ={"¸ø"};
const char PY_MB_gen[]   ={"¸ù¸ú"};
const char PY_MB_geng[]  ={"¸ü¸ı¸û¸ş¹¡¹¢¹£"};
const char PY_MB_gong[]  ={"¹¤¹­¹«¹¦¹¥¹©¹¬¹§¹ª¹¨¹®¹¯¹°¹²¹±"};
const char PY_MB_gou[]   ={"¹´¹µ¹³¹·¹¶¹¹¹º¹¸¹»"};
const char PY_MB_gu[]    ={"¹À¹¾¹Ã¹Â¹Á¹½¹¼¹¿¹Å¹È¹É¹Ç¹Æ¹Ä¹Ì¹Ê¹Ë¹Í"};
const char PY_MB_gua[]   ={"¹Ï¹Î¹Ğ¹Ñ¹Ò¹Ó"};
const char PY_MB_guai[]  ={"¹Ô¹Õ¹Ö"};
const char PY_MB_guan[]  ={"¹Ø¹Û¹Ù¹Ú¹×¹İ¹Ü¹á¹ß¹à¹Ş"};
const char PY_MB_guang[] ={"¹â¹ã¹ä"};
const char PY_MB_gui[]   ={"¹é¹ç¹ê¹æ¹ë¹è¹å¹ì¹î¹ï¹í¹ô¹ñ¹ó¹ğ¹ò"};
const char PY_MB_gun[]   ={"¹õ¹ö¹÷"};
const char PY_MB_guo[]   ={"¹ù¹ø¹ú¹û¹ü¹ı"};
const char PY_MB_ha[]    ={"¸ò¹ş"};
const char PY_MB_hai[]   ={"º¢º¡º£º¥º§º¦º¤"};
const char PY_MB_han[]   ={"º¨º©º¬ºªº¯º­º®º«º±º°ººº¹ºµº·º´º¸º¶º³º²"};
const char PY_MB_hang[]  ={"º¼º½ĞĞ"};
const char PY_MB_hao[]   ={"ºÁºÀº¿º¾ºÃºÂºÅºÆºÄ"};
const char PY_MB_he[]    ={"ºÇºÈºÌºÏºÎºÍºÓºÒºËºÉºÔºĞºÊºØºÖºÕº×"};
const char PY_MB_hei[]   ={"ºÚºÙ"};
const char PY_MB_hen[]   ={"ºÛºÜºİºŞ"};
const char PY_MB_heng[]  ={"ºàºßºãºáºâ"};
const char PY_MB_hong[]  ={"ºäºåºæºëºìºêºéºçºè"};
const char PY_MB_hou[]   ={"ºîºíºïºğºóºñºò"};
const char PY_MB_hu[]    ={"ºõºôºö»¡ºüºúºøºşºùº÷ºıºû»¢»£»¥»§»¤»¦"};
const char PY_MB_hua[]   ={"»¨»ª»©»¬»«»¯»®»­»°"};
const char PY_MB_huai[]  ={"»³»²»´»±»µ"};
const char PY_MB_huan[]  ={"»¶»¹»·»¸»º»Ã»Â»½»»»Á»¼»À»¾»¿"};
const char PY_MB_huang[] ={"»Ä»Å»Ê»Ë»Æ»Ì»Í»È»Ç»É»Ğ»Î»Ñ»Ï"};
const char PY_MB_hui[]   ={"»Ò»Ö»Ó»Ô»Õ»Ø»×»Ú»Ü»ã»á»ä»æ»å»â»ß»Ş»à»İ»Ù»Û"};
const char PY_MB_hun[]   ={"»è»ç»é»ë»ê»ì"};
const char PY_MB_huo[]   ={"»í»î»ğ»ï»ò»õ»ñ»ö»ó»ô"};
const char PY_MB_ji[]    ={"¼¥»÷¼¢»ø»ú¼¡¼¦¼£¼§»ı»ù¼¨¼©»û»ş»ü¼¤¼°¼ª¼³¼¶¼´¼«¼±¼²¼¬¼¯¼µ¼­¼®¼¸¼º¼·¼¹¼Æ¼Ç¼¿¼Í¼Ë¼É¼¼¼Ê¼Á¼¾¼È¼Ã¼Ì¼Å¼Ä¼Â¼À¼»¼½½å"};
const char PY_MB_jia[]   ={"¼Ó¼Ğ¼Ñ¼Ï¼Ò¼Î¼Ô¼Õ¼×¼Ö¼Ø¼Û¼İ¼Ü¼Ù¼Ş¼ÚĞ®"};
const char PY_MB_jian[]  ={"¼é¼â¼á¼ß¼ä¼ç¼è¼æ¼à¼ã¼ê¼å¼ğ¼ó¼í¼ë¼ñ¼õ¼ô¼ì¼ï¼ò¼î¼û¼ş½¨½¤½£¼ö¼ú½¡½§½¢½¥½¦¼ù¼ø¼ü¼ı"};
const char PY_MB_jiang[] ={"½­½ª½«½¬½©½®½²½±½°½¯½³½µ½´"};
const char PY_MB_jiao[]  ={"½»½¼½¿½½½¾½º½·½¹½¶½¸½Ç½Æ½Ê½È½Ã½Å½Â½Á½Ë½É½Ğ½Î½Ï½Ì½Ñ½Í¾õ½À"};
const char PY_MB_jie[]   ={"½×½Ô½Ó½Õ½Ò½Ö½Ú½Ù½Ü½à½á½İ½Ş½Ø½ß½ã½â½é½ä½æ½ì½ç½ê½ë½è"};
const char PY_MB_jin[]   ={"½í½ñ½ï½ğ½ò½î½ó½ö½ô½÷½õ¾¡¾¢½ü½ø½ú½ş½ı½û½ù"};
const char PY_MB_jing[]  ={"¾©¾­¾¥¾£¾ª¾§¾¦¾¬¾¤¾«¾¨¾®¾±¾°¾¯¾»¾¶¾·¾º¾¹¾´¾¸¾³¾²¾µ"};
const char PY_MB_jiong[] ={"¾¼¾½"};
const char PY_MB_jiu[]   ={"¾À¾¿¾¾¾Å¾Ã¾Ä¾Á¾Â¾Æ¾É¾Ê¾Ì¾Î¾Ç¾È¾Í¾Ë"};
const char PY_MB_ju[]    ={"¾Ó¾Ğ¾Ñ¾Ô¾Ò¾Ï¾Ö½Û¾Õ¾×¾Ú¾Ù¾Ø¾ä¾Ş¾Ü¾ß¾æ¾ã¾ç¾å¾İ¾à¾â¾Û¾á"};
const char PY_MB_juan[]  ={"¾ê¾è¾é¾í¾ë¾î¾ì"};
const char PY_MB_jue[]   ={"¾ï¾ö¾÷¾ñ¾ø¾ó¾ò¾ô¾ğ"};
const char PY_MB_jun[]   ={"¾ü¾ı¾ù¾û¾ú¿¡¿¤¾ş¿£¿¥¿¢"};
const char PY_MB_ka[]    ={"¿§¿¦¿¨"};
const char PY_MB_kai[]   ={"¿ª¿«¿­¿®¿¬"};
const char PY_MB_kan[]   ={"¼÷¿¯¿±¿°¿²¿³¿´"};
const char PY_MB_kang[]  ={"¿µ¿¶¿·¿¸¿º¿¹¿»"};
const char PY_MB_kao[]   ={"¿¼¿½¿¾¿¿"};
const char PY_MB_ke[]    ={"¿À¿Á¿Â¿Æ¿Ã¿Å¿Ä¿Ç¿È¿É¿Ê¿Ë¿Ì¿Í¿Î"};
const char PY_MB_ken[]   ={"¿Ï¿Ñ¿Ò¿Ğ"};
const char PY_MB_keng[]  ={"¿Ô¿Ó"};
const char PY_MB_kong[]  ={"¿Õ¿×¿Ö¿Ø"};
const char PY_MB_kou[]   ={"¿Ù¿Ú¿Û¿Ü"};
const char PY_MB_ku[]    ={"¿İ¿Ş¿ß¿à¿â¿ã¿á"};
const char PY_MB_kua[]   ={"¿ä¿å¿æ¿è¿ç"};
const char PY_MB_kuai[]  ={"¿é¿ì¿ë¿ê"};
const char PY_MB_kuan[]  ={"¿í¿î"};
const char PY_MB_kuang[] ={"¿ï¿ğ¿ñ¿ö¿õ¿ó¿ò¿ô"};
const char PY_MB_kui[]   ={"¿÷¿ù¿ø¿ú¿ü¿û¿ı¿şÀ¢À£À¡"};
const char PY_MB_kun[]   ={"À¤À¥À¦À§"};
const char PY_MB_kuo[]   ={"À©À¨À«Àª"};
const char PY_MB_la[]    ={"À¬À­À²À®À°À¯À±"};
const char PY_MB_lai[]   ={"À´À³Àµ"};
const char PY_MB_lan[]   ={"À¼À¹À¸À·À»À¶À¾À½ÀºÀÀÀ¿ÀÂÀÁÀÃÀÄ"};
const char PY_MB_lang[]  ={"ÀÉÀÇÀÈÀÅÀÆÀÊÀË"};
const char PY_MB_lao[]   ={"ÀÌÀÍÀÎÀÏÀĞÀÑÀÔÀÓÀÒ"};
const char PY_MB_le[]    ={"ÀÖÀÕÁË"};
const char PY_MB_lei[]   ={"À×ÀØÀİÀÚÀÙÀÜÀßÀáÀàÀÛÀŞ"};
const char PY_MB_leng[]  ={"ÀâÀãÀä"};
const char PY_MB_li[]    ={"ÀåÀæÀêÀëÀòÀçÀìÁ§ÀèÀéÀñÀîÀïÁ¨ÀíÀğÁ¦ÀúÀ÷Á¢ÀôÀöÀûÀøÁ¤ÀıÁ¥ÀşÀóÀõÀùÁ£ÀüÁ¡"};
const char PY_MB_lian[]  ={"Á¬Á±Á¯Á°Á«ÁªÁ®Á­Á²Á³Á·Á¶ÁµÁ´"};
const char PY_MB_liang[] ={"Á©Á¼Á¹ÁºÁ¸Á»Á½ÁÁÁÂÁ¾ÁÀÁ¿"};
const char PY_MB_liao[]  ={"ÁÊÁÉÁÆÁÄÁÅÁÈÁÎÁÃÁÇÁÍÁÏÁÌ"};
const char PY_MB_lie[]   ={"ÁĞÁÓÁÒÁÔÁÑ"};
const char PY_MB_lin[]   ={"ÁÚÁÖÁÙÁÜÁÕÁØÁ×ÁÛÁİÁßÁŞÁà"};
const char PY_MB_ling[]  ={"ÁæÁéÁëÁáÁèÁåÁêÁçÁâÁãÁäÁìÁîÁí"};
const char PY_MB_liu[]   ={"ÁïÁõÁ÷ÁôÁğÁòÁóÁñÁöÁøÁù"};
const char PY_MB_long[]  ={"ÁúÁüÁıÁûÂ¡ÁşÂ¤Â¢Â£"};
const char PY_MB_lou[]   ={"Â¦Â¥Â§Â¨ÂªÂ©"};
const char PY_MB_lu[]    ={"Â¶Â¬Â®Â«Â¯Â­Â±Â²Â°Â³Â½Â¼Â¸Â¹Â»ÂµÂ·Â¾ÂºÂ´"};
const char PY_MB_luan[]  ={"ÂÏÂÍÂÎÂĞÂÑÂÒ"};
const char PY_MB_lue[]   ={"ÂÓÂÔ"};
const char PY_MB_lun[]   ={"ÂÕÂØÂ×ÂÙÂÚÂÖÂÛ"};
const char PY_MB_luo[]   ={"ÂŞÂÜÂßÂàÂáÂâÂİÂãÂåÂçÂæÂä"};
const char PY_MB_lv[]    ={"ÂËÂ¿ÂÀÂÂÂÃÂÁÂÅÂÆÂÄÂÉÂÇÂÊÂÌÂÈ"};
const char PY_MB_ma[]    ={"ÂèÂéÂíÂêÂëÂìÂîÂğÂï"};
const char PY_MB_mai[]   ={"ÂñÂòÂõÂóÂôÂö"};
const char PY_MB_man[]   ={"ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
const char PY_MB_mang[]  ={"Ã¦Ã¢Ã¤Ã£Ã§Ã¥"};
const char PY_MB_mao[]   ={"Ã¨Ã«Ã¬Ã©ÃªÃ®Ã­Ã¯Ã°Ã³Ã±Ã²"};
const char PY_MB_me[]    ={"Ã´"};
const char PY_MB_mei[]   ={"Ã»Ã¶ÃµÃ¼Ã·Ã½ÃºÃ¸Ã¹Ã¿ÃÀÃ¾ÃÃÃÁÃÄÃÂ"};
const char PY_MB_men[]   ={"ÃÅÃÆÃÇ"};
const char PY_MB_meng[]  ={"ÃÈÃËÃÊÃÍÃÉÃÌÃÏÃÎ"};
const char PY_MB_mi[]    ={"ÃÖÃÔÃÕÃÑÃÓÃÒÃ×ÃĞÃÚÃÙÃØÃÜÃİÃÛ"};
const char PY_MB_mian[]  ={"ÃßÃàÃŞÃâÃãÃäÃáÃåÃæ"};
const char PY_MB_miao[]  ={"ÃçÃèÃéÃëÃìÃêÃîÃí"};
const char PY_MB_mie[]   ={"ÃğÃï"};
const char PY_MB_min[]   ={"ÃñÃóÃòÃöÃõÃô"};
const char PY_MB_ming[]  ={"ÃûÃ÷ÃùÃúÃøÃü"};
const char PY_MB_miu[]   ={"Ãı"};
const char PY_MB_mo[]    ={"ºÑÃşÄ¡Ä£Ä¤Ä¦Ä¥Ä¢Ä§Ä¨Ä©Ä­Ä°ÄªÄ¯Ä®Ä«Ä¬"};
const char PY_MB_mou[]   ={"Ä²Ä±Ä³"};
const char PY_MB_mu[]    ={"Ä¸Ä¶ÄµÄ·Ä´Ä¾Ä¿ÄÁÄ¼Ä¹Ä»ÄÀÄ½ÄºÄÂ"};
const char PY_MB_na[]    ={"ÄÃÄÄÄÇÄÉÄÈÄÆÄÅ"};
const char PY_MB_nai[]   ={"ÄËÄÌÄÊÄÎÄÍ"};
const char PY_MB_nan[]   ={"ÄĞÄÏÄÑ"};
const char PY_MB_nang[]  ={"ÄÒ"};
const char PY_MB_nao[]   ={"ÄÓÄÕÄÔÄÖÄ×"};
const char PY_MB_ne[]    ={"ÄØ"};
const char PY_MB_nei[]   ={"ÄÚÄÙ"};
const char PY_MB_nen[]   ={"ÄÛ"};
const char PY_MB_neng[]  ={"ÄÜ"};
const char PY_MB_ni[]    ={"ÄİÄáÄàÄßÄŞÄãÄâÄæÄäÄçÄå"};
const char PY_MB_nian[]  ={"ÄéÄêÄíÄìÄëÄîÄè"};
const char PY_MB_niang[] ={"ÄïÄğ"};
const char PY_MB_niao[]  ={"ÄñÄò"};
const char PY_MB_nie[]   ={"ÄóÄùÄôÄöÄ÷ÄøÄõ"};
const char PY_MB_nin[]   ={"Äú"};
const char PY_MB_ning[]  ={"ÄşÅ¡ÄüÄûÄıÅ¢"};
const char PY_MB_niu[]   ={"Å£Å¤Å¦Å¥"};
const char PY_MB_nong[]  ={"Å©Å¨Å§Åª"};
const char PY_MB_nu[]    ={"Å«Å¬Å­"};
const char PY_MB_nuan[]  ={"Å¯"};
const char PY_MB_nue[]   ={"Å±Å°"};
const char PY_MB_nuo[]   ={"Å²ÅµÅ³Å´"};
const char PY_MB_nv[]    ={"Å®"};
const char PY_MB_o[]     ={"Å¶"};
const char PY_MB_ou[]    ={"Å·Å¹Å¸Å»Å¼ÅºÅ½"};
const char PY_MB_pa[]    ={"Å¿Å¾ÅÀ°ÒÅÃÅÁÅÂ"};
const char PY_MB_pai[]   ={"ÅÄÅÇÅÅÅÆÅÉÅÈ"};
const char PY_MB_pan[]   ={"ÅËÅÊÅÌÅÍÅĞÅÑÅÎÅÏ"};
const char PY_MB_pang[]  ={"ÅÒÅÓÅÔÅÕÅÖ"};
const char PY_MB_pao[]   ={"Å×ÅÙÅØÅÚÅÛÅÜÅİ"};
const char PY_MB_pei[]   ={"ÅŞÅßÅãÅàÅâÅáÅæÅåÅä"};
const char PY_MB_pen[]   ={"ÅçÅè"};
const char PY_MB_peng[]  ={"ÅêÅéÅëÅóÅíÅïÅğÅîÅôÅìÅñÅòÅõÅö"};
const char PY_MB_pi[]    ={"±ÙÅúÅ÷ÅûÅøÅüÅùÆ¤ÅşÆ£Æ¡ÅıÆ¢Æ¥Æ¦Æ¨Æ§Æ©"};
const char PY_MB_pian[]  ={"Æ¬Æ«ÆªÆ­"};
const char PY_MB_piao[]  ={"Æ¯Æ®Æ°Æ±"};
const char PY_MB_pie[]   ={"Æ²Æ³"};
const char PY_MB_pin[]   ={"Æ´Æ¶ÆµÆ·Æ¸"};
const char PY_MB_ping[]  ={"Æ¹Æ½ÆÀÆ¾ÆºÆ»ÆÁÆ¿Æ¼"};
const char PY_MB_po[]    ={"ÆÂÆÃÆÄÆÅÆÈÆÆÆÉÆÇ"};
const char PY_MB_pou[]   ={"ÆÊ"};
const char PY_MB_pu[]    ={"¸¬ÆÍÆËÆÌÆÎÆĞÆÏÆÑÆÓÆÔÆÒÆÖÆÕÆ×ÆØ"};
const char PY_MB_qi[]    ={"ÆßÆãÆŞÆâÆàÆÜÆİÆÚÆÛÆáÆîÆëÆäÆæÆçÆíÆêÆéÆèÆïÆåÆìÆòÆóÆñÆôÆğÆøÆıÆùÆúÆûÆüÆõÆöÆ÷"};
const char PY_MB_qia[]   ={"ÆşÇ¡Ç¢"};
const char PY_MB_qian[]  ={"Ç§ÇªÇ¤Ç¨Ç¥Ç£Ç¦Ç«Ç©Ç°Ç®Ç¯Ç¬Ç±Ç­Ç³Ç²Ç´Ç·ÇµÇ¶Ç¸"};
const char PY_MB_qiang[] ={"ÇºÇ¼Ç¹Ç»Ç¿Ç½Ç¾ÇÀ"};
const char PY_MB_qiao[]  ={"ÇÄÇÃÇÂÇÁÇÇÇÈÇÅÇÆÇÉÇÎÇÍÇÏÇÌÇËÇÊ"};
const char PY_MB_qie[]   ={"ÇĞÇÑÇÒÇÓÇÔ"};
const char PY_MB_qin[]   ={"Ç×ÇÖÇÕÇÛÇØÇÙÇİÇÚÇÜÇŞÇß"};
const char PY_MB_qing[]  ={"ÇàÇâÇáÇãÇäÇåÇéÇçÇèÇæÇêÇëÇì"};
const char PY_MB_qiong[] ={"ÇîÇí"};
const char PY_MB_qiu[]   ={"ÇğÇñÇïÇôÇóÇöÇõÇò"};
const char PY_MB_qu[]    ={"ÇøÇúÇıÇüÇùÇûÇ÷ÇşÈ¡È¢È£È¥È¤"};
const char PY_MB_quan[]  ={"È¦È«È¨ÈªÈ­È¬È©È§È®È°È¯"};
const char PY_MB_que[]   ={"È²È±È³È´È¸È·ÈµÈ¶"};
const char PY_MB_qun[]   ={"È¹Èº"};
const char PY_MB_ran[]   ={"È»È¼È½È¾"};
const char PY_MB_rang[]  ={"È¿ÈÂÈÀÈÁÈÃ"};
const char PY_MB_rao[]   ={"ÈÄÈÅÈÆ"};
const char PY_MB_re[]    ={"ÈÇÈÈ"};
const char PY_MB_ren[]   ={"ÈËÈÊÈÉÈÌÈĞÈÏÈÎÈÒÈÑÈÍ"};
const char PY_MB_reng[]  ={"ÈÓÈÔ"};
const char PY_MB_ri[]    ={"ÈÕ"};
const char PY_MB_rong[]  ={"ÈÖÈŞÈ×ÈÙÈİÈÜÈØÈÛÈÚÈß"};
const char PY_MB_rou[]   ={"ÈáÈàÈâ"};
const char PY_MB_ru[]    ={"ÈçÈãÈåÈæÈäÈêÈéÈèÈëÈì"};
const char PY_MB_ruan[]  ={"ÈîÈí"};
const char PY_MB_rui[]   ={"ÈïÈñÈğ"};
const char PY_MB_run[]   ={"ÈòÈó"};
const char PY_MB_ruo[]   ={"ÈôÈõ"};
const char PY_MB_sa[]    ={"ÈöÈ÷Èø"};
const char PY_MB_sai[]   ={"ÈûÈùÈúÈü"};
const char PY_MB_san[]   ={"ÈıÈşÉ¡É¢"};
const char PY_MB_sang[]  ={"É£É¤É¥"};
const char PY_MB_sao[]   ={"É¦É§É¨É©"};
const char PY_MB_se[]    ={"É«É¬Éª"};
const char PY_MB_sen[]   ={"É­"};
const char PY_MB_seng[]  ={"É®"};
const char PY_MB_sha[]   ={"É±É³É´É°É¯ÉµÉ¶É·ÏÃ"};
const char PY_MB_shai[]  ={"É¸É¹"};
const char PY_MB_shan[]  ={"É½É¾É¼ÉÀÉºÉ¿ÉÁÉÂÉÇÉ»ÉÈÉÆÉÉÉÃÉÅÉÄÕ¤"};
const char PY_MB_shang[] ={"ÉËÉÌÉÊÉÑÉÎÉÍÉÏÉĞ"};
const char PY_MB_shao[]  ={"ÉÓÉÒÉÕÉÔÉ×ÉÖÉØÉÙÉÛÉÜÉÚ"};
const char PY_MB_she[]   ={"ÉİÉŞÉàÉßÉáÉèÉçÉäÉæÉâÉåÉã"};
const char PY_MB_shen[]  ={"ÉêÉìÉíÉëÉğÉïÉéÉîÉñÉòÉóÉôÉöÉõÉøÉ÷Ê²"};
const char PY_MB_sheng[] ={"ÉıÉúÉùÉüÊ¤ÉûÉşÊ¡Ê¥Ê¢Ê£"};
const char PY_MB_shi[]   ={"³×Ê¬Ê§Ê¦Ê­Ê«Ê©Ê¨ÊªÊ®Ê¯Ê±Ê¶ÊµÊ°Ê´Ê³Ê·Ê¸Ê¹Ê¼Ê»ÊºÊ¿ÊÏÊÀÊËÊĞÊ¾Ê½ÊÂÊÌÊÆÊÓÊÔÊÎÊÒÊÑÊÃÊÇÊÁÊÊÊÅÊÍÊÈÊÄÊÉËÆ"};
const char PY_MB_shou[]  ={"ÊÕÊÖÊØÊ×ÊÙÊÜÊŞÊÛÊÚÊİ"};
const char PY_MB_shu[]   ={"ÊéÊãÊåÊàÊâÊáÊçÊèÊæÊäÊßÊëÊêÊìÊîÊòÊğÊóÊñÊíÊïÊõÊùÊøÊöÊ÷ÊúË¡ÊüÊıÊûÊşÊô"};
const char PY_MB_shua[]  ={"Ë¢Ë£"};
const char PY_MB_shuai[] ={"Ë¥Ë¤Ë¦Ë§"};
const char PY_MB_shuan[] ={"Ë©Ë¨"};
const char PY_MB_shuang[]={"Ë«ËªË¬"};
const char PY_MB_shui[]  ={"Ë­Ë®Ë°Ë¯"};
const char PY_MB_shun[]  ={"Ë±Ë³Ë´Ë²"};
const char PY_MB_shuo[]  ={"ËµË¸Ë·Ë¶"};
const char PY_MB_si[]    ={"Ë¿Ë¾Ë½Ë¼Ë¹Ë»ËºËÀËÈËÄËÂËÅËÇËÃËÁ"};
const char PY_MB_song[]  ={"ËÉËËËÊËÏËÎËĞËÍËÌ"};
const char PY_MB_sou[]   ={"ËÔËÑËÒËÓ"};
const char PY_MB_su[]    ={"ËÕËÖË×ËßËàËØËÙËÚËÜËİËÛ"};
const char PY_MB_suan[]  ={"ËáËâËã"};
const char PY_MB_sui[]   ={"ËäËçËåËæËèËêËîËìËéËíËë"};
const char PY_MB_sun[]   ={"ËïËğËñ"};
const char PY_MB_suo[]   ={"ËôËóËòËõËùË÷ËöËø"};
const char PY_MB_ta[]    ={"ËıËûËüËúËşÌ¡Ì¢Ì¤Ì£"};
const char PY_MB_tai[]   ={"Ì¥Ì¨Ì§Ì¦Ì«Ì­Ì¬Ì©Ìª"};
const char PY_MB_tan[]   ={"Ì®Ì°Ì¯Ì²Ì±Ì³Ì¸ÌµÌ·Ì¶Ì´Ì¹Ì»ÌºÌ¾Ì¿Ì½Ì¼"};
const char PY_MB_tang[]  ={"ÌÀÌÆÌÃÌÄÌÁÌÂÌÅÌÇÌÈÌÊÌÉÌÌÌË"};
const char PY_MB_tao[]   ={"ÌÎÌĞÌÍÌÏÌÓÌÒÌÕÌÔÌÑÌÖÌ×"};
const char PY_MB_te[]    ={"ÌØ"};
const char PY_MB_teng[]  ={"ÌÛÌÚÌÜÌÙ"};
const char PY_MB_ti[]    ={"ÌŞÌİÌàÌßÌäÌáÌâÌãÌåÌëÌêÌéÌèÌæÌç"};
const char PY_MB_tian[]  ={"ÌìÌíÌïÌñÌğÌîÌóÌò"};
const char PY_MB_tiao[]  ={"µ÷ÌôÌõÌöÌ÷Ìø"};
const char PY_MB_tie[]   ={"ÌùÌúÌû"};
const char PY_MB_ting[]  ={"ÌüÍ¡ÌıÌşÍ¢Í¤Í¥Í£Í¦Í§"};
const char PY_MB_tong[]  ={"Í¨Í¬Í®Í©Í­Í¯ÍªÍ«Í³Í±Í°Í²Í´"};
const char PY_MB_tou[]   ={"ÍµÍ·Í¶Í¸"};
const char PY_MB_tu[]    ={"Í¹ÍºÍ»Í¼Í½Í¿Í¾ÍÀÍÁÍÂÍÃ"};
const char PY_MB_tuan[]  ={"ÍÄÍÅ"};
const char PY_MB_tui[]   ={"ÍÆÍÇÍÈÍËÍÉÍÊ"};
const char PY_MB_tun[]   ={"¶ÚÍÌÍÍÍÎ"};
const char PY_MB_tuo[]   ={"ÍĞÍÏÍÑÍÔÍÓÍÕÍÒÍ×ÍÖÍØÍÙ"};
const char PY_MB_wa[]    ={"ÍÛÍŞÍÚÍİÍÜÍßÍà"};
const char PY_MB_wai[]   ={"ÍáÍâ"};
const char PY_MB_wan[]   ={"ÍäÍåÍãÍèÍêÍæÍçÍéÍğÍìÍíÍñÍïÍîÍëÍòÍó"};
const char PY_MB_wang[]  ={"ÍôÍöÍõÍøÍùÍ÷ÍıÍüÍúÍû"};
const char PY_MB_wei[]   ={"Î£ÍşÎ¢Î¡ÎªÎ¤Î§Î¥Î¦Î¨Î©Î¬Î«Î°Î±Î²Î³Î­Î¯Î®ÎÀÎ´Î»Î¶Î·Î¸Î¾Î½Î¹Î¼ÎµÎ¿Îº"};
const char PY_MB_wen[]   ={"ÎÂÎÁÎÄÎÆÎÅÎÃÎÇÎÉÎÈÎÊ"};
const char PY_MB_weng[]  ={"ÎÌÎËÎÍ"};
const char PY_MB_wo[]    ={"ÎÎÎĞÎÑÎÏÎÒÎÖÎÔÎÕÎÓ"};
const char PY_MB_wu[]    ={"ÎÚÎÛÎØÎ×ÎİÎÜÎÙÎŞÎãÎâÎáÎßÎàÎåÎçÎéÎëÎäÎêÎæÎèÎğÎñÎìÎïÎóÎòÎîÎí"};
const char PY_MB_xi[]    ={"Ï¦Ï«Î÷ÎüÏ£ÎôÎöÎùÏ¢ÎşÏ¤Ï§Ï©ÎøÎúÏ¬Ï¡ÏªÎıÏ¨ÎõÎûÏ¥Ï°Ï¯Ï®Ï±Ï­Ï´Ï²Ï·ÏµÏ¸Ï¶"};
const char PY_MB_xia[]   ={"ÏºÏ¹Ï»ÏÀÏ¿ÏÁÏ¾Ï½Ï¼ÏÂÏÅÏÄ"};
const char PY_MB_xian[]  ={"Ï³ÏÉÏÈÏËÏÆÏÇÏÊÏĞÏÒÏÍÏÌÏÑÏÏÏÎÏÓÏÔÏÕÏØÏÖÏßÏŞÏÜÏİÏÚÏÛÏ×ÏÙ"};
const char PY_MB_xiang[] ={"ÏçÏàÏãÏáÏæÏäÏåÏâÏêÏéÏèÏíÏìÏëÏòÏïÏîÏóÏñÏğ"};
const char PY_MB_xiao[]  ={"ÏüÏûÏôÏõÏúÏöÏùÏıĞ¡ÏşĞ¢Ğ¤ÏøĞ§Ğ£Ğ¦Ğ¥"};
const char PY_MB_xie[]   ={"Ğ©Ğ¨ĞªĞ«Ğ­Ğ°Ğ²Ğ±Ğ³Ğ¯Ğ¬Ğ´Ğ¹ĞºĞ¶Ğ¼ĞµĞ»Ğ¸Ğ·"};
const char PY_MB_xin[]   ={"ĞÄĞÃĞ¾ĞÁĞÀĞ¿ĞÂĞ½ĞÅĞÆ"};
const char PY_MB_xing[]  ={"ĞËĞÇĞÊĞÉĞÈĞÌĞÏĞÎĞÍĞÑĞÓĞÕĞÒĞÔ"};
const char PY_MB_xiong[] ={"Ğ×ĞÖĞÙĞÚĞØĞÛĞÜ"};
const char PY_MB_xiu[]   ={"ËŞĞİĞŞĞßĞàĞãĞåĞäĞâĞá"};
const char PY_MB_xu[]    ={"ĞçĞëĞéĞêĞèĞæĞìĞíĞñĞòĞğĞôĞ÷ĞøĞïĞöĞõĞîÓõ"};
const char PY_MB_xuan[]  ={"ĞùĞûĞúĞşĞüĞıÑ¡Ñ¢Ñ¤Ñ£"};
const char PY_MB_xue[]   ={"Ï÷Ñ¥Ñ¦Ñ¨Ñ§Ñ©Ñª"};
const char PY_MB_xun[]   ={"Ñ«Ñ¬Ñ°Ñ²Ñ®Ñ±Ñ¯Ñ­ÑµÑ¶Ñ´Ñ¸Ñ·Ñ³"};
const char PY_MB_ya[]    ={"Ñ¾Ñ¹Ñ½ÑºÑ»Ñ¼ÑÀÑ¿ÑÁÑÂÑÄÑÃÑÆÑÅÑÇÑÈ"};
const char PY_MB_yan[]   ={"ÑÊÑÌÑÍÑÉÑËÑÓÑÏÑÔÑÒÑØÑ×ÑĞÑÎÑÖÑÑÑÕÑÙÑÜÑÚÑÛÑİÑáÑåÑâÑäÑçÑŞÑéÑèÑßÑæÑãÑà"};
const char PY_MB_yang[]  ={"ÑëÑêÑíÑìÑïÑòÑôÑîÑğÑñÑóÑöÑøÑõÑ÷ÑùÑú"};
const char PY_MB_yao[]   ={"½ÄÑıÑüÑûÒ¢Ò¦Ò¤Ò¥Ò¡Ò£ÑşÒ§Ò¨Ò©ÒªÒ«Ô¿"};
const char PY_MB_ye[]    ={"Ò¬Ò­Ò¯Ò®Ò²Ò±Ò°ÒµÒ¶Ò·Ò³Ò¹Ò´ÒºÒ¸"};
const char PY_MB_yi[]    ={"Ò»ÒÁÒÂÒ½ÒÀÒ¿Ò¼Ò¾ÒÇÒÄÒÊÒËÒÌÒÈÒÆÒÅÒÃÒÉÒÍÒÒÒÑÒÔÒÓÒÏÒĞÒÎÒåÒÚÒäÒÕÒéÒàÒÙÒìÒÛÒÖÒëÒØÒ×ÒïÒèÒßÒæÒêÒîÒİÒâÒçÒŞÒáÒãÒíÒÜ"};
const char PY_MB_yin[]   ={"ÒòÒõÒöÒğÒñÒôÒóÒ÷ÒúÒùÒøÒüÒıÒûÒşÓ¡"};
const char PY_MB_ying[]  ={"Ó¦Ó¢Ó¤Ó§Ó£Ó¥Ó­Ó¯Ó«Ó¨Ó©ÓªÓ¬Ó®Ó±Ó°Ó³Ó²"};
const char PY_MB_yo[]    ={"Ó´"};
const char PY_MB_yong[]  ={"Ó¶ÓµÓ¸Ó¹ÓºÓ·ÓÀÓ½Ó¾ÓÂÓ¿ÓÁÓ¼Ó»ÓÃ"};
const char PY_MB_you[]   ={"ÓÅÓÇÓÄÓÆÓÈÓÉÓÌÓÊÓÍÓËÓÎÓÑÓĞÓÏÓÖÓÒÓ×ÓÓÓÕÓÔ"};
const char PY_MB_yu[]    ={"ÓØÓÙÓåÓÚÓèÓàÓÛÓãÓáÓéÓæÓçÓäÓâÓŞÓÜÓİÓßÓëÓîÓìÓğÓêÓíÓïÓñÔ¦ÓóÓıÓôÓüÓøÔ¡Ô¤ÓòÓûÓ÷Ô¢ÓùÔ£ÓöÓúÓşÔ¥"};
const char PY_MB_yuan[]  ={"Ô©Ô§Ô¨ÔªÔ±Ô°Ô«Ô­Ô²Ô¬Ô®ÔµÔ´Ô³Ô¯Ô¶Ô·Ô¹ÔºÔ¸"};
const char PY_MB_yue[]   ={"Ô»Ô¼ÔÂÔÀÔÃÔÄÔ¾ÔÁÔ½"};
const char PY_MB_yun[]   ={"ÔÆÔÈÔÇÔÅÔÊÔÉÔĞÔËÔÎÔÍÔÏÔÌ"};
const char PY_MB_za[]    ={"ÔÑÔÓÔÒÕ¦"};
const char PY_MB_zai[]   ={"ÔÖÔÕÔÔÔ×ÔØÔÙÔÚ×Ğ"};
const char PY_MB_zan[]   ={"ÔÛÔÜÔİÔŞ"};
const char PY_MB_zang[]  ={"ÔßÔàÔá"};
const char PY_MB_zao[]   ={"ÔâÔãÔäÔçÔæÔéÔèÔåÔîÔíÔìÔëÔïÔê"};
const char PY_MB_ze[]    ={"ÔòÔñÔóÔğ"};
const char PY_MB_zei[]   ={"Ôô"};
const char PY_MB_zen[]   ={"Ôõ"};
const char PY_MB_zeng[]  ={"ÔöÔ÷Ôù"};
const char PY_MB_zha[]   ={"ÔûÔüÔúÔıÔşÕ¢Õ¡Õ£Õ§Õ©Õ¨Õ¥×õ"};
const char PY_MB_zhai[]  ={"Õ«ÕªÕ¬µÔÕ­Õ®Õ¯"};
const char PY_MB_zhan[]  ={"Õ´Õ±Õ³Õ²Õ°Õ¶Õ¹ÕµÕ¸Õ·Õ¼Õ½Õ»Õ¾ÕÀÕ¿Õº"};
const char PY_MB_zhang[] ={"³¤ÕÅÕÂÕÃÕÄÕÁÕÇÕÆÕÉÕÌÕÊÕÈÕÍÕËÕÏÕÎ"};
const char PY_MB_zhao[]  ={"ÕĞÕÑÕÒÕÓÕÙÕ×ÕÔÕÕÕÖÕØ×¦"};
const char PY_MB_zhe[]   ={"ÕÚÕÛÕÜÕİÕŞÕßÕàÕâÕãÕá×Å"};
const char PY_MB_zhen[]  ={"ÕêÕëÕìÕäÕæÕèÕåÕçÕéÕïÕíÕîÕóÕñÕòÕğÖ¡"};
const char PY_MB_zheng[] ={"ÕùÕ÷ÕúÕõÕøÕöÕôÕüÕûÕıÖ¤Ö£ÕşÖ¢"};
const char PY_MB_zhi[]   ={"Ö®Ö§Ö­Ö¥Ö¨Ö¦ÖªÖ¯Ö«Ö¬Ö©Ö´Ö¶Ö±ÖµÖ°Ö²Ö³Ö¹Ö»Ö¼Ö·Ö½Ö¸ÖºÖÁÖ¾ÖÆÖÄÖÎÖËÖÊÖÅÖ¿ÖÈÖÂÖÀÖÌÖÏÖÇÖÍÖÉÖÃ"};
const char PY_MB_zhong[] ={"ÖĞÖÒÖÕÖÑÖÓÖÔÖ×ÖÖÖÙÖÚÖØ"};
const char PY_MB_zhou[]  ={"ÖİÖÛÖßÖÜÖŞÖàÖáÖâÖãÖäÖæÖçÖåÖè"};
const char PY_MB_zhu[]   ={"ÖìÖïÖêÖéÖîÖíÖëÖñÖòÖğÖ÷ÖôÖóÖöÖõ×¡Öú×¢Öü×¤Öù×£ÖøÖûÖşÖı"};
const char PY_MB_zhua[]  ={"×¥"};
const char PY_MB_zhuai[] ={"×§"};
const char PY_MB_zhuan[] ={"×¨×©×ª×«×­"};
const char PY_MB_zhuang[]={"×±×¯×®×°×³×´´±×²"};
const char PY_MB_zhui[]  ={"×·×µ×¶×¹×º×¸"};
const char PY_MB_zhun[]  ={"×»×¼"};
const char PY_MB_zhuo[]  ={"×¿×¾×½×À×Æ×Â×Ç×Ã×Ä×Á"};
const char PY_MB_zi[]    ={"×Î×È×É×Ë×Ê×Í×Ì×Ñ×Ó×Ï×Ò×Ö×Ô×Õ"};
const char PY_MB_zong[]  ={"×Ú×Û×Ø×Ù×××Ü×İ"};
const char PY_MB_zou[]   ={"×Ş×ß×à×á"};
const char PY_MB_zu[]    ={"×â×ã×ä×å×ç×è×é×æ"};
const char PY_MB_zuan[]  ={"×¬×ë×ê"};
const char PY_MB_zui[]   ={"×ì×î×ï×í"};
const char PY_MB_zun[]   ={"×ğ×ñ"};
const char PY_MB_zuo[]   ={"×ò×ó×ô×÷×ø×ù×ö"};
const char PY_MB_space[] ={""};

/* Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×é */
struct PinYinPCB const PYRankTwoList_a[]={{"",PY_MB_a},
                                    {"i",PY_MB_ai},
                                    {"n",PY_MB_an},
                                    {"ng",PY_MB_ang},
                                    {"o",PY_MB_ao}};
struct PinYinPCB const PYRankTwoList_b[]={{"a",PY_MB_ba},
                                    {"ai",PY_MB_bai},
                                    {"an",PY_MB_ban},
                                    {"ang",PY_MB_bang},
                                    {"ao",PY_MB_bao},
                                    {"ei",PY_MB_bei},
                                    {"en",PY_MB_ben},
                                    {"eng",PY_MB_beng},
                                    {"i",PY_MB_bi},
                                    {"ian",PY_MB_bian},
                                    {"iao",PY_MB_biao},
                                    {"ie",PY_MB_bie},
                                    {"in",PY_MB_bin},
                                    {"ing",PY_MB_bing},
                                    {"o",PY_MB_bo},
                                    {"u",PY_MB_bu}};
struct PinYinPCB const PYRankTwoList_c[]={{"a",PY_MB_ca},
                                    {"ai",PY_MB_cai},
                                    {"an",PY_MB_can},
                                    {"ang",PY_MB_cang},
                                    {"ao",PY_MB_cao},
                                    {"e",PY_MB_ce},
                                    {"eng",PY_MB_ceng},
                                    {"ha",PY_MB_cha},
                                    {"hai",PY_MB_chai},
                                    {"han",PY_MB_chan},
                                    {"hang",PY_MB_chang},
                                    {"hao",PY_MB_chao},
                                    {"he",PY_MB_che},
                                    {"hen",PY_MB_chen},
                                    {"heng",PY_MB_cheng},
                                    {"hi",PY_MB_chi},
                                    {"hong",PY_MB_chong},
                                    {"hou",PY_MB_chou},
                                    {"hu",PY_MB_chu},
                                    {"huai",PY_MB_chuai},
                                    {"huan",PY_MB_chuan},
                                    {"huang",PY_MB_chuang},
                                    {"hui",PY_MB_chui},
                                    {"hun",PY_MB_chun},
                                    {"huo",PY_MB_chuo},
                                    {"i",PY_MB_ci},
                                    {"ong",PY_MB_cong},
                                    {"ou",PY_MB_cou},
                                    {"u",PY_MB_cu},
                                    {"uan",PY_MB_cuan},
                                    {"ui",PY_MB_cui},
                                    {"un",PY_MB_cun},
                                    {"uo",PY_MB_cuo}};
struct PinYinPCB const PYRankTwoList_d[]={{"a   ",PY_MB_da},
                                    {"ai",PY_MB_dai},
                                    {"an",PY_MB_dan},
                                    {"ang",PY_MB_dang},
                                    {"ao",PY_MB_dao},
                                    {"e",PY_MB_de},
                                    {"eng",PY_MB_deng},
                                    {"i",PY_MB_di},
                                    {"ian",PY_MB_dian},
                                    {"iao",PY_MB_diao},
                                    {"ie",PY_MB_die},
                                    {"ing",PY_MB_ding},
                                    {"iu",PY_MB_diu},
                                    {"ong",PY_MB_dong},
                                    {"ou",PY_MB_dou},
                                    {"u",PY_MB_du},
                                    {"uan",PY_MB_duan},
                                    {"ui",PY_MB_dui},
                                    {"un",PY_MB_dun},
                                    {"uo",PY_MB_duo}};
struct PinYinPCB const PYRankTwoList_e[]={{"",PY_MB_e},
                                    {"n",PY_MB_en},
                                    {"r",PY_MB_er}};
struct PinYinPCB const PYRankTwoList_f[]={{"a",PY_MB_fa},
                                    {"an",PY_MB_fan},
                                    {"ang",PY_MB_fang},
                                    {"ei",PY_MB_fei},
                                    {"en",PY_MB_fen},
                                    {"eng",PY_MB_feng},
                                    {"o",PY_MB_fo},
                                    {"ou",PY_MB_fou},
                                    {"u",PY_MB_fu}};
struct PinYinPCB const PYRankTwoList_g[]={{"a",PY_MB_ga},
                                    {"ai",PY_MB_gai},
                                    {"an",PY_MB_gan},
                                    {"ang",PY_MB_gang},
                                    {"ao",PY_MB_gao},
                                    {"e",PY_MB_ge},
                                    {"ei",PY_MB_gei},
                                    {"en",PY_MB_gan},
                                    {"eng",PY_MB_geng},
                                    {"ong",PY_MB_gong},
                                    {"ou",PY_MB_gou},
                                    {"u",PY_MB_gu},
                                    {"ua",PY_MB_gua},
                                    {"uai",PY_MB_guai},
                                    {"uan",PY_MB_guan},
                                    {"uang",PY_MB_guang},
                                    {"ui",PY_MB_gui},
                                    {"un",PY_MB_gun},
                                    {"uo",PY_MB_guo}};
struct PinYinPCB const PYRankTwoList_h[]={{"a",PY_MB_ha},
                                    {"ai",PY_MB_hai},
                                    {"an",PY_MB_han},
                                    {"ang",PY_MB_hang},
                                    {"ao",PY_MB_hao},
                                    {"e",PY_MB_he},
                                    {"ei",PY_MB_hei},
                                    {"en",PY_MB_hen},
                                    {"eng",PY_MB_heng},
                                    {"ong",PY_MB_hong},
                                    {"ou",PY_MB_hou},
                                    {"u",PY_MB_hu},
                                    {"ua",PY_MB_hua},
                                    {"uai",PY_MB_huai},
                                    {"uan",PY_MB_huan},
                                    {"uang ",PY_MB_huang},
                                    {"ui",PY_MB_hui},
                                    {"un",PY_MB_hun},
                                    {"uo",PY_MB_huo}};
struct PinYinPCB const PYRankTwoList_i[]={"",PY_MB_space};
struct PinYinPCB const PYRankTwoList_j[]={{"i",PY_MB_ji},
                                    {"ia",PY_MB_jia},
                                    {"ian",PY_MB_jian},
                                    {"iang",PY_MB_jiang},
                                    {"iao",PY_MB_jiao},
                                    {"ie",PY_MB_jie},
                                    {"in",PY_MB_jin},
                                    {"ing",PY_MB_jing},
                                    {"iong",PY_MB_jiong},
                                    {"iu",PY_MB_jiu},
                                    {"u",PY_MB_ju},
                                    {"uan",PY_MB_juan},
                                    {"ue",PY_MB_jue},
                                    {"un",PY_MB_jun}};
struct PinYinPCB const PYRankTwoList_k[]={{"a",PY_MB_ka},
                                    {"ai",PY_MB_kai},
                                    {"an",PY_MB_kan},
                                    {"ang",PY_MB_kang},
                                    {"ao",PY_MB_kao},
                                    {"e",PY_MB_ke},
                                    {"en",PY_MB_ken},
                                    {"eng",PY_MB_keng},
                                    {"ong",PY_MB_kong},
                                    {"ou",PY_MB_kou},
                                    {"u",PY_MB_ku},
                                    {"ua",PY_MB_kua},
                                    {"uai",PY_MB_kuai},
                                    {"uan",PY_MB_kuan},
                                    {"uang",PY_MB_kuang},
                                    {"ui",PY_MB_kui},
                                    {"un",PY_MB_kun},
                                    {"uo",PY_MB_kuo}};
struct PinYinPCB const PYRankTwoList_l[]={{"a",PY_MB_la},
                                    {"ai",PY_MB_lai},
                                    {"an",PY_MB_lan},
                                    {"ang",PY_MB_lang},
                                    {"ao",PY_MB_lao},
                                    {"e",PY_MB_le},
                                    {"ei",PY_MB_lei},
                                    {"eng",PY_MB_leng},
                                    {"i",PY_MB_li},
                                    {"ian",PY_MB_lian},
                                    {"iang",PY_MB_liang},
                                    {"iao",PY_MB_liao},
                                    {"ie",PY_MB_lie},
                                    {"in",PY_MB_lin},
                                    {"ing",PY_MB_ling},
                                    {"iu",PY_MB_liu},
                                    {"ong",PY_MB_long},
                                    {"ou",PY_MB_lou},
                                    {"u",PY_MB_lu},
                                    {"uan",PY_MB_luan},
                                    {"ue",PY_MB_lue},
                                    {"un",PY_MB_lun},
                                    {"uo",PY_MB_luo},
                                    {"v",PY_MB_lv}};
struct PinYinPCB const PYRankTwoList_m[]={{"a",PY_MB_ma},
                                    {"ai",PY_MB_mai},
                                    {"an",PY_MB_man},
                                    {"ang",PY_MB_mang},
                                    {"ao",PY_MB_mao},
                                    {"e",PY_MB_me},
                                    {"ei",PY_MB_mei},
                                    {"en",PY_MB_men},
                                    {"eng",PY_MB_meng},
                                    {"i",PY_MB_mi},
                                    {"ian",PY_MB_mian},
                                    {"iao",PY_MB_miao},
                                    {"ie",PY_MB_mie},
                                    {"in",PY_MB_min},
                                    {"ing",PY_MB_ming},
                                    {"iu",PY_MB_miu},
                                    {"o",PY_MB_mo},
                                    {"ou",PY_MB_mou},
                                    {"u",PY_MB_mu}};
struct PinYinPCB const PYRankTwoList_n[]={{"a",PY_MB_na},
                                    {"ai",PY_MB_nai},
                                    {"an",PY_MB_nan},
                                    {"ang",PY_MB_nang},
                                    {"ao",PY_MB_nao},
                                    {"e",PY_MB_ne},
                                    {"ei",PY_MB_nei},
                                    {"en",PY_MB_nen},
                                    {"eng",PY_MB_neng},
                                    {"i",PY_MB_ni},
                                    {"ian",PY_MB_nian},
                                    {"iang",PY_MB_niang},
                                    {"iao",PY_MB_niao},
                                    {"ie",PY_MB_nie},
                                    {"in",PY_MB_nin},
                                    {"ing",PY_MB_ning},
                                    {"iu",PY_MB_niu},
                                    {"ong",PY_MB_nong},
                                    {"u",PY_MB_nu},
                                    {"uan",PY_MB_nuan},
                                    {"ue",PY_MB_nue},
                                    {"uo",PY_MB_nuo},
                                    {"v",PY_MB_nv}};
struct PinYinPCB const PYRankTwoList_o[]={{"",PY_MB_o},
                                    {"u",PY_MB_ou}};
struct PinYinPCB const PYRankTwoList_p[]={{"a",PY_MB_pa},
                                    {"ai",PY_MB_pai},
                                    {"an",PY_MB_pan},
                                    {"ang",PY_MB_pang},
                                    {"ao",PY_MB_pao},
                                    {"ei",PY_MB_pei},
                                    {"en",PY_MB_pen},
                                    {"eng",PY_MB_peng},
                                    {"i",PY_MB_pi},
                                    {"ian",PY_MB_pian},
                                    {"iao",PY_MB_piao},
                                    {"ie",PY_MB_pie},
                                    {"in",PY_MB_pin},
                                    {"ing",PY_MB_ping},
                                    {"o",PY_MB_po},
                                    {"ou",PY_MB_pou},
                                    {"u",PY_MB_pu}};
struct PinYinPCB const PYRankTwoList_q[]={{"i",PY_MB_qi},
                                    {"ia",PY_MB_qia},
                                    {"ian",PY_MB_qian},
                                    {"iang",PY_MB_qiang},
                                    {"iao",PY_MB_qiao},
                                    {"ie",PY_MB_qie},
                                    {"in",PY_MB_qin},
                                    {"ing",PY_MB_qing},
                                    {"iong",PY_MB_qiong},
                                    {"iu",PY_MB_qiu},
                                    {"u",PY_MB_qu},
                                    {"uan",PY_MB_quan},
                                    {"ue",PY_MB_que},
                                    {"un",PY_MB_qun}};
struct PinYinPCB const PYRankTwoList_r[]={{"an",PY_MB_ran},
                                    {"ang",PY_MB_rang},
                                    {"ao",PY_MB_rao},
                                    {"e",PY_MB_re},
                                    {"en",PY_MB_ren},
                                    {"eng",PY_MB_reng},
                                    {"i",PY_MB_ri},
                                    {"ong",PY_MB_rong},
                                    {"ou",PY_MB_rou},
                                    {"u",PY_MB_ru},
                                    {"uan",PY_MB_ruan},
                                    {"ui",PY_MB_rui},
                                    {"un",PY_MB_run},
                                    {"uo",PY_MB_ruo}};
struct PinYinPCB const PYRankTwoList_s[]={{"a",PY_MB_sa},
                                    {"ai",PY_MB_sai},
                                    {"an",PY_MB_san},
                                    {"ang",PY_MB_sang},
                                    {"ao",PY_MB_sao},
                                    {"e",PY_MB_se},
                                    {"en",PY_MB_sen},
                                    {"eng",PY_MB_seng},
                                    {"ha",PY_MB_sha},
                                    {"hai",PY_MB_shai},
                                    {"han",PY_MB_shan},
                                    {"hang ",PY_MB_shang},
                                    {"hao",PY_MB_shao},
                                    {"he",PY_MB_she},
                                    {"hen",PY_MB_shen},
                                    {"heng",PY_MB_sheng},
                                    {"hi",PY_MB_shi},
                                    {"hou",PY_MB_shou},
                                    {"hu",PY_MB_shu},
                                    {"hua",PY_MB_shua},
                                    {"huai",PY_MB_shuai},
                                    {"huan",PY_MB_shuan},
                                    {"huang",PY_MB_shuang},
                                    {"hui",PY_MB_shui},
                                    {"hun",PY_MB_shun},
                                    {"huo",PY_MB_shuo},
                                    {"i",PY_MB_si},
                                    {"ong",PY_MB_song},
                                    {"ou",PY_MB_sou},
                                    {"u",PY_MB_su},
                                    {"uan",PY_MB_suan},
                                    {"ui",PY_MB_sui},
                                    {"un",PY_MB_sun},
                                    {"uo",PY_MB_suo}};
struct PinYinPCB const PYRankTwoList_t[]={{"a",PY_MB_ta},
                                    {"ai",PY_MB_tai},
                                    {"an",PY_MB_tan},
                                    {"ang",PY_MB_tang},
                                    {"ao",PY_MB_tao},
                                    {"e",PY_MB_te},
                                    {"eng",PY_MB_teng},
                                    {"i",PY_MB_ti},
                                    {"ian",PY_MB_tian},
                                    {"iao",PY_MB_tiao},
                                    {"ie",PY_MB_tie},
                                    {"ing",PY_MB_ting},
                                    {"ong",PY_MB_tong},
                                    {"ou",PY_MB_tou},
                                    {"u",PY_MB_tu},
                                    {"uan",PY_MB_tuan},
                                    {"ui",PY_MB_tui},
                                    {"un",PY_MB_tun},
                                    {"uo",PY_MB_tuo}};
struct PinYinPCB const PYRankTwoList_u[]={{"",PY_MB_space}};
struct PinYinPCB const PYRankTwoList_v[]={{"",PY_MB_space}};
struct PinYinPCB const PYRankTwoList_w[]={{"a",PY_MB_wa},
                                    {"ai",PY_MB_wai},
                                    {"an",PY_MB_wan},
                                    {"ang",PY_MB_wang},
                                    {"ei",PY_MB_wei},
                                    {"en",PY_MB_wen},
                                    {"eng",PY_MB_weng},
                                    {"o",PY_MB_wo},
                                    {"u",PY_MB_wu}};
struct PinYinPCB const PYRankTwoList_x[]={{"i",PY_MB_xi},
                                    {"ia",PY_MB_xia},
                                    {"ian",PY_MB_xiao},
                                    {"iang",PY_MB_xiang},
                                    {"iao",PY_MB_xiao},
                                    {"ie",PY_MB_xie},
                                    {"in",PY_MB_xin},
                                    {"ing",PY_MB_xing},
                                    {"iong",PY_MB_xiong},
                                    {"iu",PY_MB_xiu},
                                    {"u",PY_MB_xu},
                                    {"uan",PY_MB_xuan},
                                    {"ue",PY_MB_xue},
                                    {"un",PY_MB_xun}};
struct PinYinPCB const PYRankTwoList_y[]={{"a",PY_MB_ya},
                                    {"an",PY_MB_yan},
                                    {"ang",PY_MB_yang},
                                    {"ao",PY_MB_yao},
                                    {"e",PY_MB_ye},
                                    {"i",PY_MB_yi},
                                    {"in",PY_MB_yin},
                                    {"ing",PY_MB_ying},
                                    {"o",PY_MB_yo},
                                    {"ong",PY_MB_yong},
                                    {"ou",PY_MB_you},
                                    {"u",PY_MB_yu},
                                    {"uan",PY_MB_yuan},
                                    {"ue",PY_MB_yue},
                                    {"un",PY_MB_yun}};
struct PinYinPCB const PYRankTwoList_z[]={{"a",PY_MB_za},
                                    {"ai",PY_MB_zai},
                                    {"an",PY_MB_zan},
                                    {"ang",PY_MB_zang},
                                    {"ao",PY_MB_zao},
                                    {"e",PY_MB_ze},
                                    {"ei",PY_MB_zei},
                                    {"en",PY_MB_zen},
                                    {"eng",PY_MB_zeng},
                                    {"ha",PY_MB_zha},
                                    {"hai",PY_MB_zhai},
                                    {"han",PY_MB_zhan},
                                    {"hang",PY_MB_zhang},
                                    {"hao",PY_MB_zhao},
                                    {"he",PY_MB_zhe},
                                    {"hen",PY_MB_zhen},
                                    {"heng",PY_MB_zheng},
                                    {"hi",PY_MB_zhi},
                                    {"hong",PY_MB_zhong},
                                    {"hou",PY_MB_zhou},
                                    {"hu",PY_MB_zhu},
                                    {"hua",PY_MB_zhua},
                                    {"huai",PY_MB_zhuai},
                                    {"huan",PY_MB_zhuan},
                                    {"huang",PY_MB_zhuang},
                                    {"hui",PY_MB_zhui},
                                    {"hun",PY_MB_zhun},
                                    {"huo",PY_MB_zhuo},
                                    {"i",PY_MB_zi},
                                    {"ong",PY_MB_zong},
                                    {"ou",PY_MB_zou},
                                    {"u",PY_MB_zu},
                                    {"uan",PY_MB_zuan},
                                    {"ui",PY_MB_zui},
                                    {"un",PY_MB_zun},
                                    {"uo",PY_MB_zuo}};
struct PinYinPCB const PYRankTwoList_end[]={"",PY_MB_space};
/* Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×éµÄÖ¸Õë */
struct PinYinPCB const *PYRankThreeList[]={  PYRankTwoList_a,
                                            PYRankTwoList_b,
                                            PYRankTwoList_c,
                                            PYRankTwoList_d,
                                            PYRankTwoList_e,
                                            PYRankTwoList_f,
                                            PYRankTwoList_g,
                                            PYRankTwoList_h,
                                            PYRankTwoList_i,
                                            PYRankTwoList_j,
                                            PYRankTwoList_k,
                                            PYRankTwoList_l,
                                            PYRankTwoList_m,
                                            PYRankTwoList_n,
                                            PYRankTwoList_o,
                                            PYRankTwoList_p,
                                            PYRankTwoList_q,
                                            PYRankTwoList_r,
                                            PYRankTwoList_s,
                                            PYRankTwoList_t,
                                            PYRankTwoList_u,
                                            PYRankTwoList_v,
                                            PYRankTwoList_w,
                                            PYRankTwoList_x,
                                            PYRankTwoList_y,
                                            PYRankTwoList_z,
                                            PYRankTwoList_end
										};

/*******************************************************************************
* Function Name  : PYSearch
* Description    : ¼ìË÷Æ´ÒôµÄº¯Êı
* Input          : - msg: ¼ìË÷Æ´ÒôµÄÊı×é
* Output         : None
* Return         : Èç¹ûÕâ¸öÆ´Òô´æÔÚºº×ÖÓëÆä¶ÔÓ¦£¬·µ»Ø¼ìË÷µ½µÄºº×ÖµÄÖ¸Õë£¬Èç¹ûÃ»ÓĞ£¬·µ»Ø¿ÕÖ¸Õë
* Attention		 : None
*******************************************************************************/
char *PYSearch(unsigned char *msg)
{
	unsigned char count = 0;
	unsigned char i = 0;
	struct PinYinPCB const *headpcb; 			/* ÀıÈç¡®b'£¬ÒÔ¶ÁÒôÎª¡¯b'¿ªÍ·µÄËùÓĞºº×Ö */
	struct PinYinPCB const *tailpcb;			/* ¡®b'µÄÏÂÒ»¸ö¡®c'£¬ÒÔ¶ÁÒôÎª¡¯c'¿ªÍ·µÄËùÓĞºº×Ö */
												/* Í¨¹ıÕâ±È½ÏÁ½¸öÊı¾İµÄ´óĞ¡¿ÉÒÔµÃµ½¡¯b'µÄËùÓĞµÄÔªÒô+¸¨Òô */
	while( msg[count] != 0 ) count++;			/* ¼ÆËã¼ìË÷µÄÆ´ÒôµÄ×Ö½ÚÊı */		
	for( i=0; i<count; i++ )					/* ¼ì²é¼ìË÷µÄÆ´ÒôÊÇ·ñ·ûºÏ¹æ·¶ */
	{
	   if( (msg[i] >= 'a') && (msg[i] <= 'z') ) /* ÔÚÕâ¸öÇø¼äµÄÊı¾İÓĞĞ§ */
	   {
		  continue;
	   }
	   else if( (msg[i] >= 'A') && (msg[i] <= 'Z') )	/* Èç¹ûÊÇ´óĞ´£¬Í³Ò»±ä³ÉĞ¡Ğ´ */
	   {
		  msg[i] += 0x20;						
		  continue;
	   }									   
	  else										/* ÊäÈëµÄÊı¾İ·Ç·¨£¬·µ»Ø	*/
	  {
		  return '\0';
	  }
	}
	if( (*msg == 'i') || (*msg == 'u') || (*msg == 'v') || (*msg == '\0') )	 /* ÊäÈëµÄÊı¾İ·Ç·¨£¬·µ»Ø */
	{
	    return '\0';
	}
	tailpcb = PYRankThreeList[*msg-'a'];	 	/* ÒÔ¶ÁÒôÎª*msg¿ªÍ·µÄËùÓĞÆ´Òô¼ìË÷ */
	headpcb = PYRankThreeList[*msg-'a'+1];		/* ÒÔ¶ÁÒôÎª*msg+1¿ªÍ·µÄËùÓĞÆ´Òô¼ìË÷ */
	for( ;tailpcb < headpcb; tailpcb++ )
	{
	    for( i=0; i < count-1; i++ )			/* ¼ì²éÊäÈëµÄÆ´ÒôÓë¼ìË÷½á¹¹ÌåÖĞµÄÆ´ÒôÊÇ·ñÒ»ÖÂ */
		{	
			if( *((*tailpcb).PYSerList+i) != msg[i+1] )
			{
			    break;
			}
		}
		if( i == (count-1) )	 				/* Ò»ÖÂ£¬Êä³öÖ¸Õë */
		{
		    return (char *)(*tailpcb).PYRankOneList;
		}		
	}
	return '\0';								/* ·ñÕß·µ»Ø¿ÕµÄÖ¸Õë */
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

	
	

	

