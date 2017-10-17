/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Keyboard.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = gpJeu->loadImg("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    ostringstream os2;
    int tmp;
    switch (id) {
        case 1 : texte = "Objet de troc*Parle � la bonne personne pour �changer."; break;
        case 2 : texte = "Tu ne peux pas p�cher ici, cherche un ponton."; break;
        case 3 : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Tu as trouv� un quart de coeur !!!";
            if (tmp<4) buffer = "Encore "+os.str()+" et tu gagneras un coeur suppl�mentaire !!!";
            else buffer = "Ton nombre de coeurs vient d'augmenter !!!";
            break;
        case 4 : texte = "Ca te prend souvent de parler aux arbres ???"; break;
        case 5 : texte = "Maison de Link**Ne pas approcher."; break;
        case 6 : texte = "N : Vers le village Cocorico"; break;
        case 7 : texte = "E : Vers la cit� d'Hyrule"; break;
        case 8 : texte = "Tu n'as rien attrap�."; break;
        case 9 : texte = "Tu as p�ch� une �crevisse!"; break;
        case 10 : texte = "Tu as p�ch� un �perlan!"; break;
        case 11 : texte = "Tu as p�ch� un poisson z�bre!"; break;
        case 12 : texte = "Tu as p�ch� un gobie!"; break;
        case 13 : texte = "Tu as p�ch� un crabe!"; break;
        case 14 : texte = "Tu as p�ch� une pibale!"; break;
        case 15 : texte = "Tu as p�ch� un vairon!"; break;
        case 16 : texte = "Tu as p�ch� un carassin dor�!"; break;
        case 17 : texte = "Tu as p�ch� une ablette!"; break;
        case 18 : texte = "Tu as p�ch� un goujon!"; break;
        case 19 : texte = "Tu as p�ch� une loche!"; break;
        case 20 : texte = "Tu as p�ch� une �pinoche!"; break;
        case 21 : texte = "Tu as p�ch� une gr�mille!"; break;
        case 22 : texte = "Tu as p�ch� une blennie!"; break;
        case 23 : texte = "Tu as p�ch� un magicarpe!"; buffer="Mais rien ne se passe..."; break;
        case 24 : texte = "Tu as p�ch� une truite!*C'est un gros poisson!"; break;
        case 25 : texte = "Tu as p�ch� un ayu!*C'est un gros poisson!"; break;
        case 26 : texte = "Tu as p�ch� une perche noire!*C'est un gros poisson!"; break;
        case 27 : texte = "Tu as p�ch� une anguille!*C'est un gros poisson!"; break;
        case 28 : texte = "Tu as p�ch� un poisson-chat!*C'est un gros poisson!"; break;
        case 29 : texte = "Tu as p�ch� un black-bass!*C'est un gros poisson!"; break;
        case 30 : texte = "Tu as p�ch� un huchon!*C'est un gros poisson!"; break;
        case 31 : texte = "Tu as p�ch� un barbeau!*C'est un gros poisson!"; break;
        case 32 : texte = "Tu as p�ch� une lamproie!*C'est un gros poisson!"; break;
        case 33 : texte = "Tu as p�ch� un hotu!*C'est un gros poisson!"; break;
        case 34 : texte = "Tu as p�ch� un saumon!*C'est un poisson �norme!"; break;
        case 35 : texte = "Tu as p�ch� un esturgeon!*C'est un poisson �norme!"; break;
        case 36 : texte = "Tu as p�ch� un omble chevalier!*C'est un poisson �norme!"; break;
        case 37 : texte = "Tu as p�ch� une carpe!*C'est un poisson �norme!"; break;
        case 38 : texte = "Tu as p�ch� un silure!*C'est un poisson �norme!"; break;
        case 39 : texte = "Tu as trouv� une gemme de force !**Troque-les en ville contre des prix."; break;
        case 40 : 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_DEVANT_CHEZ_LINK) {id=44; chercheText();break;}
            texte = "Bonjour Link!*Tu fais une dr�le de t�te, tu dormais ?"; idsuiv=41; break;
        case 41 : texte = "La princesse veux te voir de toute urgence au ch�teau!"; idsuiv=42; break;
        case 42 : texte = "..."; idsuiv=43; break;
        case 43 : texte = "..."; idsuiv=44; break;
        case 44 : texte = "Le ch�teau. A l'est d'ici, tu n'as tout de m�me pas oubli� ?"; break;
        case 45 : texte = "Hum Hum..."; idsuiv=46; break;
        case 46 : texte = "TUTORIEL : Appuyez sur Cercle pr�s de quelqu'un pour lui parler, ou pr�s d'une pancarte pour la lire."; break;
        case 47 : texte = "Tu n'as appris aucun th�me.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=48; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=57; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=59; chercheText();break;}
            break;
        case 48 : texte = "- CHANT DE L'ENVOL*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=50; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=61; chercheText();break;}
            break;
        case 49 : texte = "- Chant de l'envol*- NE RIEN JOUER"; break;
        case 50 : texte = "- CHANT DE L'ENVOL*- Chant du temps invers�*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=53; chercheText();break;}
            break;
        case 51 : texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Ne rien jouer"; break;
        case 52 : texte = "- Chant de l'envol*- Chant du temps invers�*- NE RIEN JOUER"; break;
        case 53 : texte = "- CHANT DE L'ENVOL*- Chant du temps invers�*- Chant du temps acc�l�r�*- Ne rien jouer"; break;
        case 54 : texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Chant du temps acc�l�r�*- Ne rien jouer"; break;
        case 55 : texte = "- Chant de l'envol*- Chant du temps invers�*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 56 : texte = "- Chant de l'envol*- Chant du temps invers�*- Chant du temps acc�l�r�*- NE RIEN JOUER"; break;
        case 57 : texte = "- CHANT DU TEMPS INVERSE*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=64; chercheText();break;}
            break;
        case 58 : texte = "- Chant du temps invers�*- NE RIEN JOUER"; break;
        case 59 : texte = "- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 60 : texte = "- Chant du temps acc�l�r�*- NE RIEN JOUER"; break;
        case 61 : texte = "- CHANT DE L'ENVOL*- Chant du temps acc�l�r�*- Ne rien jouer"; break;
        case 62 : texte = "- Chant de l'envol*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 63 : texte = "- Chant de l'envol*- Chant du temps acc�l�r�*- NE RIEN JOUER"; break;
        case 64 : texte = "- CHANT DU TEMPS INVERSE*- Chant du temps acc�l�r�*- Ne rien jouer"; break;
        case 65 : texte = "- Chant du temps invers�*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 66 : texte = "- Chant du temps invers�*- Chant du temps acc�l�r�*- NE RIEN JOUER"; break;
        case 67 : texte = "Sans effet..."; break;
        case 68 : texte = "Domaine de Link*Propri�t� priv�e"; break;
        case 69 : texte = "Cit� d'Hyrule"; break;
        case 70 : texte = "Il n'y a pas l'air d'avoir de poissons ici..."; break;
        case 71 : texte = "N : Vers le Ch�teau d'Hyrule"; break;
        case 72 : texte = "Le ch�teau est plus au nord, d�p�che-toi!"; break;
        case 73 : texte = "Le ch�teau est de l'autre c�t� du pont, h�te-toi!"; break;
        case 74 : texte = "La princesse t'attend au ch�teau, au nord d'ici."; break;
        case 75 : texte = "Tu n'as pas assez."; break;
        case 76 : texte = "Reviens si tu changes d'avis."; break;
        case 77 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>-1) {id=80; chercheText();break;}
            texte = "Un rouage contre un poulet et 100 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 78 : texte = "Un rouage contre un poulet et 100 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 79 : texte = "Tu as obtenu un rouage!*Va vite le donner � l'homme pr�s des cascades!"; break;
        case 80 : 
            if ((gpJeu->getJoueur()->getCoeur(14) && gpJeu->getZone()==18)
            || (gpJeu->getJoueur()->getCoeur(15) && gpJeu->getZone()==3)) {
                id=82; chercheText();break;}
            texte = "Un quart de coeur contre un roc magma et un roc givre ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 81 : texte = "Un quart de coeur contre un roc magma et un roc givre ?*              oui              NON ?"; idsuiv=76; break;
        case 82 : texte = "D�sol�, je n'ai plus rien en stock."; break;
        case 83 : 
            if (gpJeu->getJoueur()->getRubisMax()>=200) {id=86; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10
            || gpJeu->getJoueur()->getTroc(M_PLUME)<1) idsuiv=75;
            break;
        case 84 : texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 85 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'� 200 rubis!"; break;
        case 86 : 
            if (gpJeu->getJoueur()->getRubisMax()>=500) {id=89; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1) idsuiv=75;
            break;
        case 87 : texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 88 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'� 500 rubis!!!"; break;
        case 89 : 
            if (gpJeu->getJoueur()->getRubisMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 90 : texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 91 : texte = "Tu as obtenu une �norme bourse!!!*Tu vas pouvoir transporter jusqu'� 999 rubis!!!"; break;
        case 92 : 
            texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_RIZ)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<3) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 93 : texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              oui              NON ?"; idsuiv=76; break;
        case 94 : texte = "Tu as obtenu un poulet!"; break;
        case 95 : texte = "Tu ne peux pas en porter plus..."; break;
        case 96 : 
            texte = "Une plume contre 2 bocaux d'�pices et 2 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 97 : texte = "Une plume contre 2 bocaux d'�pices et 2 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 98 : texte = "Tu as obtenu une plume!"; break;
        case 99 : 
            texte = "Un sac de riz contre 15 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 100 : texte = "Un sac de riz contre 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 101 : texte = "Tu as obtenu un sac de riz!"; break;
        case 102 : 
            texte = "Un sac d'olives contre 10 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 103 : texte = "Un sac d'olives contre 10 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 104 : texte = "Tu as obtenu un sac d'olives!"; break;
        case 105 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>2) {id=112; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==2 
            && gpJeu->getJoueur()->getObjet()==15) {id=106; chercheText();break;}
            texte = "J'ai l'impression d'avoir pass� ma vie � balayer...*Un de ces jours je partirai bien en voyage pour changer..."; break;
        case 106 : texte = "C'est une carte de voyage que tu as l� ? *Tu veux bien me la donner ? Je r�ve de faire du tourisme!"; idsuiv=107; break;
        case 107 : texte = "Je t'offre mon balai en �change, tu es d'accord ?*              OUI ?            non  "; idsuiv=109; break;
        case 108 : texte = "Je t'offre mon balai en �change, tu es d'accord ?*              oui              NON ?"; idsuiv=110; break;
        case 109 : texte = "Merci! Voici mon balai en r�compense. C'est un tr�s bon balai, il est dans ma famille depuis des si�cles, tu fais une affaire!"; break;
        case 110 : texte = "J'imagine que je n'ai plus qu'� balayer dans ce cas..."; break;
        case 111 : texte = "Tu as troqu� la carte de voyage contre un balai!"; break;
        case 112 : texte = "Bien, o� vais-je partir ?"; break;
        case 113 : texte = "Parfois dans mes r�ves je les mange � la broche..."; break;
        case 114 : texte = "Cette ville regorge de boutiques en tout genre, dommage qu'aucune d'entre elles ne m'int�resse..."; break;
        case 115 : texte = "Depuis que la paix est revenue, la princesse Zelda a fait �norm�ment pour Hyrule. Il n'y aurait pas de villes aussi prosp�res que celle-ci sans elle."; break;
        case 116 : texte = "Le troc est le seul moyen de se procurer certains objets rares, ou de quoi faire sa cuisine."; break;
        case 117 : texte = "Ma maman me dit toujours de ne pas jouer avec les poules... Pourquoi ?"; break;
        case 118 : texte = "La princesse tient � ce que nous assurions la s�curit� de la ville... Tout le monde sait pourtant que Ganon est mort..."; break;
        case 119 : texte = "Je pr�f�rerais dormir au ch�teau que monter la garde ici..."; break;
        case 120 : texte = "La vie est belle en Hyrule depuis que Ganon n'est plus une menace, merci encore Link!"; break;
        case 121 : texte = "Depuis le vol au ch�teau, la princesse a doubl� la garde... et me revoil� de corv�e..."; break;
        case 122 : texte = "Engagez-vous... Rengagez-vous qu'ils disaient..."; break;
        case 123 : texte = "J'ai entendu dire qu'un objet de valeur a �t� vol� au palais, et depuis la princesse serait devenue compl�tement parano...";
            buffer="Ca devait �tre un objet auquel elle tenait beaucoup... Un miroir de sa collection sans doute..."; break;
        case 124 : texte = "Zzzzz... Zzzzz..."; break;
        case 125 : texte = "N : Vers le ch�teau de Ganon"; break;
        case 126 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) {id=82; chercheText();break;}
            texte = "La perle de Lune contre une roue, une jauge, une source d'�nergie et 100 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_ROUE)<1
            || gpJeu->getJoueur()->getTroc(M_JAUGE)<1
            || gpJeu->getJoueur()->getTroc(M_SOURCE_ENERGIE)<1) idsuiv=75;
            break;
        case 127 : texte = "La perle de Lune contre une roue, une jauge, une source d'�nergie et 100 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 128 : texte = "Tu as obtenu la perle de Lune!*Tu retrouves ton apparence normale et l'usage de ton �quipement!"; break;
        case 129 : 
            if (gpJeu->getJoueur()->getGanonMax()>=200) {id=132; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10
            || gpJeu->getJoueur()->getTroc(M_PERLES)<1) idsuiv=75;
            break;
        case 130 : texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 131 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'� 200 Ganon d'or!"; break;
        case 132 : 
            if (gpJeu->getJoueur()->getGanonMax()>=500) {id=135; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1) idsuiv=75;
            break;
        case 133 : texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 134 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'� 500 Ganon d'or!!!"; break;
        case 135 : 
            if (gpJeu->getJoueur()->getGanonMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<250
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 136 : texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 137 : texte = "Tu as obtenu une �norme bourse!!!*Tu vas pouvoir transporter jusqu'� 999 Ganon d'or!!!"; break;
        case 138 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUE)>-1) {id=141; chercheText();break;}
            texte = "Une roue contre 3 bocaux d'�pices ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 139 : texte = "Une roue contre 3 bocaux d'�pices ?**              oui              NON ?"; idsuiv=76; break;
        case 140 : texte = "Tu as obtenu une roue!*...*Super..."; break;
        case 141 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=82; chercheText();break;}
            texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'�pices ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)<1
            || gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 142 : texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'�pices ?**              oui              NON ?"; idsuiv=76; break;
        case 143 : texte = "Tu as obtenu un sac de bombes!*Tu vas pouvoir d�blayer des nouveaux chemins!"; break;
        case 144 : 
            texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)>=99) idsuiv=95;
            break;
        case 145 : texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              oui              NON ?"; idsuiv=76; break;
        case 146 : texte = "Tu as obtenu un roc magma!"; break;
        case 147 : 
            texte = "Des perles contre 5 bocaux d'�pices et 5 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 148 : texte = "Des perles contre 5 bocaux d'�pices et 5 Ganon d'or ?**              oui              NON ?"; idsuiv=76; break;
        case 149 : texte = "Tu as obtenu des perles!"; break;
        case 150 : 
            texte = "Un bocal d'�pices contre 10 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 151 : texte = "Un bocal d'�pices contre 10 Ganon d'or ?**              oui              NON ?"; idsuiv=76; break;
        case 152 : texte = "Tu as obtenu un bocal d'�pices!"; break;
        case 153 : texte = "Hi! Hi! Hiiiiiiii!"; break;
        case 154 : texte = "L'autre soir le barman n'avait plus de bi�re...*Ganon est devenu rouge de col�re et a tout d�truit...*Au final plus personne n'a rien � boire..."; break;
        case 155 : texte = "Les maisons d�truites �taient celles d'opposants � Ganon..."; 
            buffer="Le bar est d�truit lui aussi, mais... ...pour d'autres raisons..."; break;
        case 156 : texte = "La place du march� est la principale activit� de la ville maintenant que le bar a �t� d�truit..."; break;
        case 157 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) texte = "Tu as obtenu la perle de Lune ?*Enfin vu le r�sultat c'�tait peut-�tre pas une affaire...";
            else texte = "La perle de Lune permet de retrouver une apparence humaine, mais le marchand qui en a une la vend beaucoup trop ch�re..."; break;
        case 158 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "N : Terres Sacr�es - Camping interdit"; break;
        case 159 : 
            if (gpJeu->getJoueur()->getPieceMax()>=200) {id=162; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 pi�ces d'or contre un poulet et 10 pi�ces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 160 : texte = "Une bourse pouvant contenir 200 pi�ces d'or contre un poulet et 10 pi�ces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 161 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'� 200 pi�ces d'or!"; break;
        case 162 : 
            if (gpJeu->getJoueur()->getPieceMax()>=500) {id=165; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 pi�ces d'or contre un parfum et 100 pi�ces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<100
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 163 : texte = "Une bourse pouvant contenir 500 pi�ces d'or contre un parfum et 100 pi�ces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 164 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'� 500 pi�ces d'or!!!"; break;
        case 165 : 
            if (gpJeu->getJoueur()->getPieceMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 pi�ces d'or contre une tapisserie, un roc magma et 250 pi�ces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<250
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 166 : texte = "Une bourse pouvant contenir 999 pi�ces d'or contre une tapisserie, un roc magma et 250 pi�ces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 167 : texte = "Tu as obtenu une �norme bourse!!!*Tu vas pouvoir transporter jusqu'� 999 pi�ces d'or!!!"; break;
        case 168 : 
            texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 169 : texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 170 : texte = "Tu as obtenu une amulette!"; break;
        case 171 : 
            texte = "Une plume contre un bocal d'�pices et un sac d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 172 : texte = "Une plume contre un bocal d'�pices et un sac d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 173 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Avec tous ces loups, quitter le village est devenu tr�s dangereux..."; break;
        case 174 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Tes armes ressemblent � celles des chevaliers...*Tu as d�j� affront� des loups avec ?"; break;
        case 175 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je d�teste les poules, mais si les loups p�n�trent dans le village, ils n'oseront peut-�tre pas approcher..."; break;
        case 176 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Les torches aux entr�es du village tiennent les loups � l'�cart, mais ils approchent de plus en plus chaque jour..."; break;
        case 177 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Le chef du village a fait construire un bar derni�rement... D'apr�s les rumeurs il aurait agit ainsi pour attirer les chevaliers hyliens et nous faire b�n�ficier de leur protection..."; break;
        case 178 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (!gpJeu->getJoueur()->getPieceMax()) {id=771; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>3) {id=185; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==3 
            && gpJeu->getJoueur()->getObjet()==15) {id=179; chercheText();break;}
            texte = "Quand les choses vont mal, je fais des confitures pour m'occuper... Mais en cette saison il va falloir que je trouve une autre activit�..."; break;
        case 179 : texte = "Tu as un balai � me proposer ?*Je sens une vocation na�tre en moi... Tu me le c�des contre mon dernier pot de confiture ?"; idsuiv=180; break;
        case 180 : texte = "Ce balai contre un pot de confiture, ok ?**              OUI ?            non  "; idsuiv=182; break;
        case 181 : texte = "Ce balai contre un pot de confiture, ok ?**              oui              NON ?"; idsuiv=183; break;
        case 182 : texte = "Cool! Je vais pouvoir me changer les id�es, et peut-�tre m�me faire fuir les loups avec ce balai!"; break;
        case 183 : texte = "Je suis s�re que tu me le donneras t�t ou tard..."; break;
        case 184 : texte = "Tu as troqu� le balai contre un pot de confiture!"; break;
        case 185 : texte = "Donner c'est donner!"; break;
        case 186 : texte = "Ch�teau d'Hyrule"; break;
        case 187 : texte = "N : Vers le cimeti�re"; break;
        case 188 : texte = "Bienvenue au ch�teau, Messire Link!"; break;
        case 189 : texte = "Nous avons ordre de vous laisser passer."; break;
        case 190 : texte = "Ch�teau de Ganon"; break;
        case 191 : 
            texte = "5 Ganon d'or et nous te laissons aller et venir au ch�teau ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) idsuiv=75;
            break;
        case 192 : texte = "5 Ganon d'or et nous te laissons aller et venir au ch�teau ?*              oui              NON ?"; idsuiv=76; break;
        case 193 : texte = "Tu peux entrer."; break;
        case 194 : texte = "QUE LE CHEMIN DE LA TRIFORCE TE SOIT OUVERT...*VOIS APPARAITRE LE TEMPLE DE LA TRIFORCE!"; break;
        case 195 : texte = "O : Vers le Ch�teau d'Hyrule"; break;
        case 196 : texte = "N : Vers les cascades"; break;
        case 197 : texte = "E : Entr�e des bois perdus"; break;
        case 198 : 
            tmp = 6-(gpJeu->getJoueur()->nbCristaux());
            os << tmp;
            texte = "Tu as trouv� un cristal magique !!!";
            if (tmp>0) buffer = "Encore "+os.str()+" � trouver !";
            else buffer = "Tu les as enfin tous !!!";
            break;
        case 199 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 200 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 201 : texte = "Partie sauvegard�e."; break;
        
        case 202 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>6) {id=209; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==6 
            && gpJeu->getJoueur()->getObjet()==11) {id=203; chercheText();break;}
            texte = "Je construis un op�ra ici, je n'ai pas le temps de bavarder durant la pause!"; 
            buffer="En plus j'ai perdu mon accessoire vedette..."; break;
        case 203 : texte = "Tu as trouv� mon cr�ne f�tiche ???*Je l'avais oubli� en prison...*Rend-le-moi! Je te serais �ternellement redevable!"; idsuiv=204; break;
        case 204 : texte = "Ce cr�ne contre ma gratitude, ok ?**              OUI ?            non  "; idsuiv=206; break;
        case 205 : texte = "Ce cr�ne contre ma gratitude, ok ?**              oui              NON ?"; idsuiv=207; break;
        case 206 : texte = "Merci! Je retrouve toute ma motivation! Je vais achever cet op�ra!"; buffer="Apr�s une pause..."; break;
        case 207 : texte = "Voleur..."; break;
        case 208 : texte = "Tu as troqu� le cr�ne contre une reconnaissance de dette!"; break;
        case 209 : texte = "Etre ou ne pas �tre ? Telle est la question..."; buffer="Le ton est bon ?"; break;
        case 210 : texte = "Temple du Courage**Courage, fuyez!"; break;
        case 211 : texte = "Bienvenue chez Tingle!"; break;
        case 212 : texte = "Temple de l'Air**Risque de rhume!"; break;
        case 213 : texte = "S : Vers le village des Mouettes"; break;
        case 214 : texte = "Village des Mouettes"; break;
        case 215 : 
            texte = "Une tapisserie contre 2 perles et 5 bocaux d'�pices ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)>=99) idsuiv=95;
            break;
        case 216 : texte = "Une tapisserie contre 2 perles et 5 bocaux d'�pices ?*              oui              NON ?"; idsuiv=76; break;
        case 217 : texte = "Tu as obtenu une tapisserie!"; break;
        case 218 : 
            texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<5
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 219 : texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 220 : 
            texte = "Des perles contre 2 bocaux d'�pices et 2 sacs de riz ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 221 : texte = "Des perles contre 2 bocaux d'�pices et 2 sacs de riz ?*              oui              NON ?"; idsuiv=76; break;
        case 222 : 
            texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 223 : texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              oui              NON ?"; idsuiv=76; break;
        case 224 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "Les hommes du village sont tous obnubil�s par le concours de p�che...*Je me demande qui gagnera..."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "Tu participes au concours de p�che ?*...*..."; buffer="Finalement tu es comme tous les autres...";} 
            else {texte = "Tu as gagn� le concours de p�che ?*...*..."; buffer="Je suis ta plus grande fan!!!";}
            break;
        case 225 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "Un stand de p�che vient d'ouvrir � l'ouest du village...*Le proprio organise un grand concours de p�che pour inaugurer sa boutique."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "Tu participes aussi au concours de p�che ? *C'est d�sesp�rant, je n'arrive pas � trouver plus de 3 sortes de poissons...";} 
            else {texte = "Depuis que le concours de p�che est fini, chacun est retourn� � ses activit�s.";}
            break;
        case 226 : texte = "Vi l ge     Mo  t  s"; break;
        case 227 : 
            texte = "Repaire des Preux Chevaliers";
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE)
            texte += "**NB : Si nous ne sommes pas l�, passez voir � la taverne."; break;
        case 228 :
            if (gpJeu->getJoueur()->getGemme(91)) {id=230; chercheText();break;}
            texte = "Une gemme de force contre 2 perles ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2) idsuiv=75;
            break;
        case 229 : texte = "Une gemme de force contre 2 perles ?**              oui              NON ?"; idsuiv=76; break;
        case 230 : 
            if (gpJeu->getJoueur()->getGemme(92)) {id=232; chercheText();break;}
            texte = "Une gemme de force contre 2 plumes ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<2) idsuiv=75;
            break;
        case 231 : texte = "Une gemme de force contre 2 plumes ?**              oui              NON ?"; idsuiv=76; break;
        case 232 : 
            if (gpJeu->getJoueur()->getGemme(93)) {id=82; chercheText();break;}
            texte = "Une gemme de force contre 2 poulets ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<2) idsuiv=75;
            break;
        case 233 : texte = "Une gemme de force contre 2 poulets ?**              oui              NON ?"; idsuiv=76; break;
        case 234 : 
            texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_OLIVES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 235 : texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              oui              NON ?"; idsuiv=76; break;
        case 236 : texte = "Au-del� de la fronti�re Sud d'Hyrule, on dit que se dresse un vaste oc�an..."; buffer="A la belle saison des mouettes franchissent les falaises qui nous s�parent de la plage et viennent jusqu'� ce village."; break;
        case 237 : texte = "Ce village est sous la protection des chevaliers Hyliens, tu es donc en s�curit� ici."; 
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE) 
            buffer="Toutefois, depuis qu'une taverne a ouvert dans un village voisin, on ne voit plus beaucoup nos protecteurs dans le coin..."; break;
        case 238 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>2) {id=245; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==2 
            && gpJeu->getJoueur()->getObjet()==7) {id=239; chercheText();break;}
            texte = "Pas ici non plus ? Qu'est-ce que j'ai bien pu en faire ?"; break;
        case 239 : texte = "Tu as retrouv� le vase de ma belle-m�re ??? *Ca fait des semaines qu'elle me force � le chercher partout! *D�p�che-toi de me le rendre!"; idsuiv=240; break;
        case 240 : texte = "Ce vase contre un truc que je viens de trouver, ok ?*              OUI ?            non  "; idsuiv=242; break;
        case 241 : texte = "Ce vase contre un truc que je viens de trouver, ok ?*              oui              NON ?"; idsuiv=243; break;
        case 242 : texte = "Sage d�cision petit."; break;
        case 243 : texte = "Tuez-le..."; break;
        case 244 : texte = "Tu as troqu� la botte contre un marteau!"; break;
        case 245 : texte = "Ca te dirait d'entrer dans mon gang ?**              OUI ?            non  "; idsuiv=247; break;
        case 246 : texte = "Ca te dirait d'entrer dans mon gang ?**              oui              NON ?"; idsuiv=243; break;
        case 247 : texte = "Ha! Ha! Ha! *Je rigolais, tu es brave, mais sot! *Insecte ridicule! *Sais-tu bien qui nous sommes ?"; break;
        case 248 : texte = "Temple de la Sagesse**Seuls les sages sauront s'en tenir � l'�cart."; break;
        case 249 : texte = "Stand de location de barques"; break;
        case 250 : texte = "Le stand de barques est ferm� pour l'instant, je suis bien parti pour remporter le concours de p�che, j'en ai d�j� 3 diff�rents!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->hasObjet(O_PALMES)) {id=1378; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_BARQUE)) {id=253; chercheText();break;}
            texte = "Veux-tu louer une barque pour 15 rubis ?**              OUI ?            non  "; idsuiv=253;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            break;
        case 252 : texte = "Veux-tu louer une barque pour 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 253 : texte = "Tu peux utiliser la barque au ponton, amuse-toi bien, mais ne t'�loigne pas trop."; break;
        case 254 : texte = "(voix lointaine :) *J'ai dit... NE T'ELOIGNE PAS TROP!!!!"; break;
        case 255 : texte = "Grotte des Abysses**Merci de ne pas venir chercher le descendant des sages qui n'est pas cach� l�."; break;
        case 256 : texte = "Forgeron"; break;
        case 257 : texte = "Grande Pyramide"; break;
        case 258 : texte = "INDICE 1 : La pierre la plus � droite est la seconde. *INDICE 2 : Les pierres doivent �tre �t�es dans l'ordre de leurs poids."; break;
        case 259 : texte = "INDICE 3 : Les pierres de la queue doivent �tre �t�es avant celle de la nageoire. *INDICE 4 : La pierre de l'oeil doit �tre �t�e en 5�me."; break;
        case 260 : texte = "INDICE 5 : Les pierres aquatiques doivent �tre �t�es avant la derni�re de la queue. *INDICE 6 : La pierre de l'oeil doit �tre �t�e apr�s celle de la nageoire."; break;
        case 261 : texte = "INDICE 7 : La derni�re pierre n'est pas l'oeil. *INDICE 8 : Les 2 pierres de la queue ne doivent pas �tre �t�es cons�cutivement."; break;
        case 262 : texte = "INDICE 9 : L'un des 9 indices est faux."; break;
        case 263 : texte = "N : Montagnes Rocheuses"; break;
        case 264 : texte = "Village Cocorico"; break;
        case 265 : 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) {id=82; chercheText();break;}
            texte = "Les bottes de P�gase contre une tapisserie et un parfum ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 266 : texte = "Les bottes de P�gase contre une tapisserie et un parfum ?*              oui              NON ?"; idsuiv=76; break;
        case 267 : texte = "Tu as obtenu les bottes de P�gase ! *Maintiens R pour courir !"; break;
        case 268 : 
            texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<3
            || gpJeu->getJoueur()->getTroc(M_RIZ)<4) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PARFUM)>=99) idsuiv=95;
            break;
        case 269 : texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              oui              NON ?"; idsuiv=76; break;
        case 270 : texte = "Tu as obtenu un parfum !"; break;
        case 271 : 
            texte = "Un sac d'olives contre 15 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 272 : texte = "Un sac d'olives contre 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 273 : 
            texte = "Un bocal d'�pices contre 20 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 274 : texte = "Un bocal d'�pices contre 20 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 275 : texte = "Le village Cocorico est un passage oblig� pour les aventuriers qui souhaitent gravir la montagne. Les moins courageux se contentent d'atteindre le saloon..."; break;
        case 276 : texte = "Soit le bienvenu au village, Link! *Amuse-toi, mais �vite tout de m�me de trop t'approcher des cactus..."; break;
        case 277 : texte = "Les bottes de P�gase permettent de se d�placer beaucoup plus rapidement. Cela donne un r�el avantage au combat."; 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) buffer="Tu as ces bottes ? *Tu dois �tre plut�t fort d�sormais..."; break;
        case 278 : 
            texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>=99) idsuiv=95;
            break;
        case 279 : texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              oui              NON ?"; idsuiv=76; break;
        case 280 : texte = "Tu as obtenu un roc givre !"; break;
        case 281 : 
            texte = "Des perles contre un bocal d'�pices et un sac de riz ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 282 : texte = "Des perles contre un bocal d'�pices et un sac de riz ? *              oui              NON ?"; idsuiv=76; break;
        case 283 : texte = "Ce village est sous la protection des 7 sages. Gr�ce � leur magie, il faut pas mal s'�loigner avant d'apercevoir les premiers loups..."; break;
        case 284 : texte = "Tu es ici au village le plus s�r que tu pourras trouver. Rien � voir avec le hameau du centre vou� � dispara�tre, ni avec le village de l'Est d�fendu par des alcooliques..."; break;
        case 285 : texte = "Temple du Temps"; break;
        case 286 : texte = "Entr�e de la mine"; break;
        case 287 : texte = "Temple de la Force**R�serv� aux costauds."; break;
        case 288 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>2) {id=295; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==2 
            && gpJeu->getJoueur()->getObjet()==11) {id=289; chercheText();break;}
            texte = "Je me suis isol� du monde pour m�diter sur le sens de la vie..."; buffer="...mais je dois bien admettre que certaines choses me manquent..."; break;
        case 289 : texte = "C'est une bouteille de vin que tu as l� ??? *Donne-la-moi! Je te donnerai de l'or en �change !!!"; idsuiv=290; break;
        case 290 : texte = "Cette bouteille contre de l'or, ok ?**              OUI ?            non  "; idsuiv=292; break;
        case 291 : texte = "Cette bouteille contre de l'or, ok ?**              oui              NON ?"; idsuiv=293; break;
        case 292 : texte = "Je sens que j'approche de la v�rit� !"; break;
        case 293 : texte = "...*Je vais devoir m�diter sur le sens de ton refus..."; break;
        case 294 : texte = "Tu as troqu� la bouteille contre de la poudre d'or!"; break;
        case 295 : texte = "J'ai enfin trouv� le sens de la vie... Hic!"; break;
        case 296 : texte = "Tour de Glace**Le chemin s'ouvrira lorsque toutes les gemmes de force auront �t� trouv�es."; break;
        case 297 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>1) {id=304; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==1 
            && gpJeu->getJoueur()->getObjet()==3) {id=298; chercheText();break;}
            texte = "D'ici je peux admirer le lac de lave... *D'ailleurs j'adore tout ce qui est rouge et qui brille."; break;
        case 298 : texte = "Mmm... c'est une magnifique gemme que tu as l�... *Tu me la donnerais contre... une surprise ?"; idsuiv=299; break;
        case 299 : texte = "Cette gemme rouge contre une surprise, ok ?**              OUI ?            non  "; idsuiv=301; break;
        case 300 : texte = "Cette gemme rouge contre une surprise, ok ?**              oui              NON ?"; idsuiv=302; break;
        case 301 : texte = "Merci! Voil� ta surprise! Depuis le temps que je cherchais � m'en d�barrasser..."; break;
        case 302 : texte = "Tans pis pour toi, pas de gemme pas de surprise."; break;
        case 303 : texte = "Tu as troqu� la gemme rouge contre une enclume! Tu ne peux plus courir ni nager jusqu'� ce que tu t'en d�barrasses!"; break;
        case 304 : texte = "Je me sens plus l�ger et plus riche, que du bonheur!"; break;
        case 305 : texte = "Temple du Feu"; break;
        case 306 : texte = "Nous sommes des rennes qui parlent."; break;
        case 307 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>4) {id=314; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==4 
            && gpJeu->getJoueur()->getObjet()==7) {id=308; chercheText();break;}
            texte = "Nous avons �chou� ici apr�s avoir percut� une mouette... *Tout �a ne serait jamais arriv� si j'avais eu un klaxon..."; 
            buffer = "Ah oui j'oubliais : *Ho! Ho! Ho!"; break;
        case 308 : texte = "C'est une clochette que tu as l� ? *Ca me donne une id�e... *Tu me la c�derais ? Je n'ai plus de poney, mais je devrais bien trouver de quoi te remercier..."; idsuiv=309; break;
        case 309 : texte = "Cette clochette contre une r�compense, ok ?**              OUI ?            non  "; idsuiv=311; break;
        case 310 : texte = "Cette clochette contre une r�compense, ok ?**              oui              NON ?"; idsuiv=312; break;
        case 311 : texte = "Merci! Voil� ta r�compense : la hache que je devais livrer en cadeau au bourreau du coin. Heureux ?"; break;
        case 312 : texte = "... *Quel est ton nom ?*Je te raye de ma liste."; break;
        case 313 : texte = "Tu as troqu� la clochette contre une hache!"; break;
        case 314 : texte = "Ho! Ho! Ho!"; buffer="C'est bien gentil, mais comment je rentre moi ?"; break;
        case 315 : texte = "TUTORIEL :*Un choc sur une de ces sph�res de couleur permute les obstacles lev�s."; break;
        case 316 : texte = "Tu as trouv� une �p�e !!!*Sert-en avec la touche Carr�, ou maintiens Carr� enfonc� pour charger une attaque tornade!"; break;
        case 317 : texte = "TUTORIEL :*Tomber dans un trou permet de descendre au niveau inf�rieur, cependant, s'il n'y a pas de niveau inf�rieur tel que c'est le cas ici, une chute fait perdre de la vie et renvoie � l'entr�e de la zone. Prudence donc!"; break;
        case 318 : texte = "TUTORIEL :*Au cours du jeu, vous pourriez �tre amen� � rencontrer des zones apparemment inaccessibles comme la plate-forme en bas. Vous aurez alors"; buffer="besoin de revenir plus tard dans le jeu avec un �quipement plus fournit pour y acc�der."; break;
        case 319 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 320 : texte = "Les gardes t'ont aper�u te diriger vers la for�t, j'ai pens� que tu avais une piste et j'ai accouru..."; break;
        case 321 : texte = "Mmm... Cette st�le est en hylien ancien... Je vais te la traduire :"; idsuiv=322; break;
        case 322 : texte = "A l'aube du cataclysme, le h�ros trouvera cette st�le. Les pendentifs du courage, de la sagesse et de la force en sa possession, l'unique chance de sauver le monde se pr�sentera � lui."; break;
        case 323 : texte = "..."; buffer="J'ai peur que nous devions laisser tomber cette affaire d'ocarina pour le moment...*Si cette st�le dit vrai, tu dois trouver les 3 pendentifs dans les plus brefs d�lais..."; idsuiv=324; break;
        case 324 : texte = "Ils sont cach�s dans 3 temples, le plus proche est une tour pr�s des cascades au Nord d'ici... Prends cette carte, elle t'aidera � t'orienter!"; break;
        case 325 : texte = "Tu as obtenu la carte d'Hyrule!**Appuie sur L � l'ext�rieur pour la consulter."; break;
        case 326 : 
            if (!gpJeu->getJoueur()->hasMedaillon(0)) {texte = "Le premier m�daillon se trouve dans la tour au Nord de cette for�t, sors de la for�t par l'Ouest puis va au Nord pour arriver dans la zone des cascades."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(1)) {texte = "Le second m�daillon se trouve dans le temple au milieu du lac. Tu devras louer une barque pr�s du village des Mouettes..."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(2)) {texte = "Le dernier m�daillon est dans un temple dans les montagnes, au Nord du village Cocorico."; break;}
            if (gpJeu->getJoueur()->getEpee()<2) {id=327; chercheText();break;}
            id=329; chercheText();break;
        case 327 : texte = "Tu as trouv� tous les pendentifs ?*Bien, nous ignorons tout de ce qui va se passer, alors prends cette �p�e avec toi."; break;
        case 328 : texte = "Tu as obtenu Excalibur !!!*Sa puissance devrait t'�tre utile!"; break;
        case 329 : 
            if (gpJeu->getJoueur()->getAvancement() == PORTAIL_F_OUVERT) {texte = "On dirait un portail de t�l�portation, mais... ...nous n'avons aucune information quant � sa destination..."; break;}
            texte = "Essaie de toucher la st�le, il va s�rement se passer quelque chose maintenant que tu as les pendentifs..."; break;
        case 330 : texte = "Une derni�re chose :*Des monstres commencent � appara�tre partout en Hyrule... C'est tr�s mauvais signe... Soit prudent."; break;
        case 331 : 
            texte = "Bonjour Link, les visiteurs se font rares ces temps-ci...";
            if (gpJeu->getJoueur()->getBouclier()!=1) {idsuiv=333; break;}
            buffer="Laisse-moi am�liorer ton bouclier..."; break;
        case 332 : texte = "Tu as obtenu un meilleur bouclier !!!*Ta d�fense augmente d'un point!"; break;
        case 333 : texte = "Viens me voir si tu es bless�, je te soignerai."; break;
        case 334 : texte = "Tu as obtenu 10 sacs de riz!"; break;
        case 335 : texte = "Tu as obtenu 10 bocaux d'�pices!"; break;
        case 336 : texte = "Tu as obtenu 10 sacs d'olives!"; break;
        case 337 : texte = "Pour ouvrir l'acc�s � la Pyramide, trouve et note les 9 indices cach�s sur des pancartes du d�sert, puis soul�ve les pierres de la baleine dans le bon ordre, et le chemin s'ouvrira..."; break;
        case 338 :
            if (gpJeu->getJoueur()->getAvancement() < GARS_MINE_AIDE) {
                texte = "Chariot express : Je suis absent pour le moment, en cas d'urgence, je suis au saloon.** - L'employ� de la mine -"; break;}
            texte = "Chariot express : le service a repris!"; break;
        case 339 : texte = "Monte dans le wagonnet et laisse-moi m'occuper du levier. *Ne t'inqui�te pas c'est mon m�tier!"; break;
        case 340 : texte = "Tu as trouv� des planches de bois!*Tu pourrais t'en servir pour construire un pont..."; break;
        case 341 : texte = "Ca semble �tre un bon endroit pour construire un pont."; break;
        case 342 : texte = "                      Link*                 H�ros d'Hyrule*               - Tu� par Ganon -"; break;
        case 343 : texte = "Nous sommes au complet, nous allons t'ouvrir le portail..."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Pr�pare-toi bien, le voleur de l'ocarina doit �tre une cr�ature tr�s puissante..."; break;}
            texte = "Tu as r�ussi � reprendre l'ocarina ? F�licitation !"; break;
        case 345 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Ce portail est tr�s particulier, il pointe vers un endroit pr�cis du pass�... Mais nous ne pourrons pas le maintenir ouvert �ternellement, d�p�che-toi!"; break;}
            texte = "Tu as l'ocarina ? Nous avons donc accompli la mission confi�e par nos anc�tres..."; break;
        case 346 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Le portail est enfin ouvert... Va Link, tu dois reprendre l'ocarina!"; break;}
            texte = "L'Ocarina du Temps..."; buffer="Cours au Temple du Temps, accomplit ta destin�e!"; break;
        case 347 : texte = "Lorsque nous serons au complet et munis de la cl� du temps, nous t'ouvrirons le portail..."; break;
        case 348 : texte = "Tu as r�ussi... Nous refermons le portail..."; break;
        case 349 : texte = "Tu as obtenu une jauge!*...*Cool..."; break;
        case 350 :
            if ((gpJeu->getJoueur()->getBombeMax()<30 && gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
            || gpJeu->getJoueur()->getFlecheMax()<70)
                {id=351; chercheText();break;}
            if (!gpJeu->getJoueur()->hasObjet(O_RECUP_FLECHE) 
            || !gpJeu->getJoueur()->hasObjet(O_RECUP_BOMBE))
                {id=356; chercheText();break;}
            texte = "Ca va j'ai assez d'or, va-t'en."; break;
            break;
        case 351 : 
            texte = "Donne-moi vite 100 Ganon d'or si tu veux une r�compense, ok ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100) idsuiv=75;
            break;
        case 352 : texte = "Donne-moi vite 100 Ganon d'or si tu veux une r�compense, ok ?*              oui              NON ?"; idsuiv=353; break;
        case 353 : texte = "Tu me fais perdre mon temps, oust!"; break;
        case 354 : texte = "Je vais augmenter le nombre de fl�ches que tu peux transporter.*Merci qui ?"; break;
        case 355 : texte = "Je vais augmenter le nombre de bombes que tu peux transporter.*Je suis trop bonne..."; break;
        case 356 : 
            texte = "Donne-moi 999 Ganon d'or si tu veux une super r�compense, ok ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<999) idsuiv=75;
            break;
        case 357 : texte = "Donne-moi 999 Ganon d'or si tu veux une super r�compense, ok ?*              oui              NON ?"; idsuiv=353; break;
        case 358 : texte = "Ton nombre de fl�ches va d�sormais augmenter en permanence, n'h�site plus � les utiliser."; break;
        case 359 : texte = "Ton stock de bombe se restitue d�sormais en permanence, tu peux exploser sans compter!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) {id=333; chercheText();break;}
            texte = "Bienvenue � toi h�ros, je vais augmenter ta r�serve de magie, �a devrait t'�tre utile."; break;
        case 361 : texte = "Ta r�serve de magie a doubl�!"; break;
        case 362 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je te sers quelque chose ?"; break;
        case 363 : texte = "D'apr�s les rumeurs, une f�e se cacherait derri�re une cascade...*Quelle sornette..."; break;
        case 364 : texte = "Je euh... monte la garde dans le bar, oui voil�.*Mais je pr�f�rerai que �a reste entre nous, ok?"; break;
        case 365 : texte = "H�ros d'Hyrule ou pas, ne pense pas boire � l'oeil."; break;
        case 366 : texte = "C'est trop risqu� de rentrer ici, on risque de te voir."; break;
        case 367 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getZone()==84 && gpJeu->getJoueur()->getNbGemmes() == 200 
            && gpJeu->getJoueur()->getGemme() == 0) {id=405; chercheText(); break;}
            texte = "Choisis ce que tu veux.*"; break;
        case 368 : texte = "10 fl�ches pour 20 rubis ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75; break;
        case 369 : texte = "10 fl�ches pour 20 rubis ?**              oui              NON ?"; break;
        case 370 : texte = "5 bombes pour 30 rubis ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=75; break;
        case 371 : texte = "5 bombes pour 30 rubis ?**              oui              NON ?"; break;
        case 372 : texte = "Il te faut un sac de bombes pour acheter ceci."; break;
        case 373 : texte = "Il te faut un arc pour acheter ceci."; break;
        case 374 : texte = "Tu n'as pas besoin de �a."; break;
        case 375 : texte = "Merci."; break;
        case 376 : texte = "Un petit coeur pour 5 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 377 : texte = "Un petit coeur pour 5 rubis ?**              oui              NON ?"; break;
        case 378 : texte = "Une petite fiole de magie pour 15 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75; break;
        case 379 : texte = "Une petite fiole de magie pour 15 rubis ?**              oui              NON ?"; break;
        case 380 : texte = "Une grande fiole de magie pour 25 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=75; break;
        case 381 : texte = "Une grande fiole de magie pour 25 rubis ?**              oui              NON ?"; break;
        case 382 :
            if (gpJeu->getJoueur()->getAvancement()<APPREND_POUR_ROC_GIVRE) {texte = "Je viens d'arriver dans cette ville, je ne suis pas encore ouvert, reviens plus tard."; break;}
            if (gpJeu->getJoueur()->getAvancement()==APPREND_POUR_ROC_GIVRE 
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)==-1) {
                texte = "Est-ce que j'ai un roc givre ?*Oui, tout juste."; idsuiv=383; break;
            }
            texte = "Je pensais que personne n'avait de gemmes de force, j'h�sitais � ouvrir ma boutique, mais tu m'as d�cid�.";
            buffer = "D�s ta prochaine visite je serai ouvert, tu pourras acheter des articles rarissimes contre des gemmes.";
            break;
        case 383 : texte = "Je te le c�de pour 30 gemmes de force, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<30) idsuiv=385; break;
        case 384 : texte = "Je te le c�de pour 30 gemmes de force, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 385 : texte = "Tu n'as pas assez de gemmes.*Cherche mieux, on en trouve partout."; break;
        case 386 : texte = "Ce d�tecteur permet de voir si tu as trouv� toutes les gemmes de force de ta zone actuelle. Un outil indispensable pour trouver toutes les gemmes, il est � toi contre 20 gemmes de force!"; idsuiv=387; break;
        case 387 : texte = "Le d�tecteur pour 20 gemmes de force, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 388 : texte = "Le d�tecteur pour 20 gemmes de force, ok ?**              oui              NON ?"; break;
        case 389 : texte = "Tu as obtenu le d�tecteur !*Lorsque tu appuies sur D-Pad droit, le nombre de gemmes en ta possession sera �crit en vert si tu les as toutes dans la zone."; break;
        case 390 : 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=393; chercheText(); break;}
            texte = "Une bouteille vide pour 10 gemmes de force ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<10) idsuiv=385; break;
        case 391 : texte = "Une bouteille vide pour 10 gemmes de force ?**              oui              NON ?"; break;
        case 392 : texte = "Tu as obtenu une bouteille !*Tu vas pouvoir stocker des potions dedans !"; break;
        case 393 : texte = "Une bouteille vide pour 20 gemmes de force ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 394 : texte = "Une bouteille vide pour 20 gemmes de force ?**              oui              NON ?"; break;
        case 395 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_FORCE)==1) {id=398; chercheText(); break;}
            texte = "Une augmentation de ta force pour 20 gemmes ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 396 : texte = "Une augmentation de ta force pour 20 gemmes ?**              oui              NON ?"; break;
        case 397 : texte = "Ta force augmente d'un point!"; break; 
        case 398 : 
            texte = "Une augmentation de ta force pour 40 gemmes ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 399 : texte = "Une augmentation de ta force pour 40 gemmes ?**              oui              NON ?"; break;
        case 400 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_DEFENSE)==1) {id=403; chercheText(); break;}
            texte = "Une augmentation de ta d�fense pour 20 gemmes ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 401 : texte = "Une augmentation de ta d�fense pour 20 gemmes ? *              oui              NON ?"; break;
        case 402 : texte = "Ta d�fense augmente d'un point!"; break; 
        case 403 : 
            texte = "Une augmentation de ta d�fense pour 40 gemmes ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 404 : texte = "Une augmentation de ta d�fense pour 40 gemmes ? *              oui              NON ?"; break;
        case 405 : texte = "Mmm... mon stock est vide..."; idsuiv=406; break;
        case 406 : texte = "Tu as d� trouver toutes les gemmes de force, c'est incroyable..."; idsuiv=407; break;
        case 407 : texte = "D'apr�s une vielle l�gende, quand toutes les gemmes auront �t� trouv�es, un temple gardant un tr�sor fabuleux s'ouvrira...*Plus qu'� attendre..."; break;
        case 408 : texte = "Reviens me voir lorsque tu auras un flacon vide et je te vendrais des potions."; break;
        case 409 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'�nergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=410; break;
        case 410 : texte = "Que d�sires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=413; break;
        case 411 : texte = "Que d�sires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=415; break;
        case 412 : texte = "Que d�sires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 413 : texte = "Une potion rouge pour 60 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=75; break;
        case 414 : texte = "Une potion rouge pour 60 rubis ?**              oui              NON ?"; break;
        case 415 : texte = "Une potion verte pour 40 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=75; break;
        case 416 : texte = "Une potion verte pour 40 rubis ?**              oui              NON ?"; break;
        case 417 : texte = "Tu as trouv� une potion rouge !!!**Bois-la pour restaurer toute ton �nergie!!!"; break;
        case 418 : texte = "Tu as trouv� une potion verte !!!**Bois-la pour restaurer toute ta magie!!!"; break;
        case 419 : texte = "Tu as trouv� une potion bleue !!!**Bois-la pour restaurer ton �nergie et ta magie!!!"; break;
        case 420 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 421 : texte = "                D�j� fatigu� ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 422 : texte = "                D�j� fatigu� ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 423 : texte = "                D�j� fatigu� ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 424 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=431; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==3 
            && gpJeu->getJoueur()->getObjet()==3) {id=425; chercheText();break;}
            texte = "Je suis l'homme le plus malchanceux du pays, il ne m'arrive jamais rien de bon..."; break;
        case 425 : texte = "C'est un porte-bonheur que tu as l� ? *Donne-le-moi! *Personne n'en a autant besoin que moi!"; idsuiv=426; break;
        case 426 : texte = "Ce fer � cheval contre... rien, ok ?**              OUI ?            non  "; idsuiv=428; break;
        case 427 : texte = "Ce fer � cheval contre... rien, ok ?**              oui              NON ?"; idsuiv=429; break;
        case 428 : texte = "Merci mille fois! Je vais peut-�tre avoir de la chance maintenant!"; 
            buffer = "Par contre d�sol� l'ami, mais je n'ai rien � t'offrir en �change, on dirait que la chance a tourn�."; break;
        case 429 : texte = "... *Quelle immonde d�veine!"; break;
        case 430 : texte = "Tu as troqu� le fer � cheval contre... sa reconnaissance ?"; break;
        case 431 : texte = "Finalement je suis un sacr� veinard."; break;
        case 432 : texte = "Je n'ai plus de prix � mettre en jeu, d�sol�."; break;
        case 433 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            if (tmp==0) {id=432; chercheText();break;}
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "Il y a "+os.str()+" prix dans ces 9 coffres, tu veux tenter ta chance pour "+os2.str()+" rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<(4-tmp+1)*5) idsuiv=75; break;
        case 434 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "Il y a "+os.str()+" prix dans ces 9 coffres, tu veux tenter ta chance pour "+os2.str()+" rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              oui              NON ?"; break;
        case 435 : texte = "Choisis un coffre."; break;
        case 436 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 437 : texte = "Perdu! Ce coffre est vide."; break;
        case 438 :
            if (gpJeu->getJoueur()->hasObjet(O_SAC_TROC)) {id=444; chercheText();break;}
            texte = "Bonjour Link, tu veux traverser le pont pour acc�der au temple ?"; idsuiv=439;
            break;
        case 439 : texte = "Habituellement je n'aurais qu'� activer ce levier, mais j'ai jou� avec toute la soir�e d'hier, et euh... je l'ai cass�."; 
            buffer="J'ai m�me pens� � mettre des planches en bois pour permettre de passer, mais on m'a vol� mes planches la nuit derni�re..."; idsuiv=440; break;
        case 440 : texte = "Je pourrais toujours r�parer le levier, mais j'ai besoin d'une pi�ce de rechange, et je ne peux pas quitter mon poste..."; idsuiv=441; break;
        case 441 : texte = "J'ai besoin d'un rouage, on en trouve sur la place du march� de la cit� d'Hyrule."; idsuiv=442; break;
        case 442 : texte = "Tu connais le principe, non ? Chaque marchand te propose des marchandises contre d'autres, tu dois r�unir ce qu'ils veulent pour obtenir ce que tu veux."; idsuiv=443; break;
        case 443 : texte = "Je vais te donner les marchandises que j'ai.*Si tu veux consulter ce que tu as d�j�, appuie sur D-Pad gauche."; break;
        case 444 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)==0) {id=446; chercheText();break;}
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>0) {id=445; chercheText();break;}
            texte = "Il me faut un rouage pour r�parer le levier.*Va en chercher sur la place du march� de la cit� d'Hyrule si tu veux franchir le pont."; break;
        case 445 : texte = "Tu as un rouage ?*Bien, �a devrait marcher maintenant."; break;
        case 446 : texte = "Le levier est � nouveau cass�...*Au moins le pont est sorti cette fois...*Ca m'apprendra � construire des ponts excentriques..."; break;
        case 447 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas d��u...*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=75; break;
        case 448 : texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas d��u...*              oui              NON ?"; break;
        case 449 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>1) {id=456; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==1 
            && gpJeu->getJoueur()->getObjet()==15) {id=450; chercheText();break;}
            texte = "J'adore tout ce qui est vert et qui brille!"; 
            buffer = "Ne t'en fais pas, je ne vais pas te voler de rubis... *J'essaie d'arr�ter."; break;
        case 450 : texte = "C'est dr�lement beau ce que tu as l�... *J'adore!*Je te l'�change contre une carte de voyage d'une valeur... euh... INESTIMABLE!"; idsuiv=451; break;
        case 451 : texte = "Cette gemme verte contre une carte, ok ?**              OUI ?            non  "; idsuiv=453; break;
        case 452 : texte = "Cette gemme verte contre une carte, ok ?**              oui              NON ?"; idsuiv=454; break;
        case 453 : texte = "Merciiii!!! Voil� ta carte de voyage, maintenant du vent!"; break;
        case 454 : texte = "Tr�s bien... *Surveille tes Rubis dans ce cas!"; break;
        case 455 : texte = "Tu as troqu� la gemme verte contre une carte!"; break;
        case 456 : texte = "Tu es venu me donner des Rubis ?*Comme c'est gentil!"; break;
        case 457 : texte = "La princesse veut que je la pr�vienne s'il se passe quelque chose de curieux en ville..."; 
            buffer = "Ce matin j'ai vu une mouette qui volait curieusement... j'h�site � lui en parler..."; break;
        case 458 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)) {id=478; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() == PARLE_PECHE) {id=460; chercheText();break;}
            gpJeu->getJoueur()->setAvancement(PARLE_PECHE);
            texte = "Bonjour Link, soit le bienvenu au stand de p�che!"; idsuiv = 459; break;
        case 459 : texte = "Pour inaugurer l'ouverture du stand, j'organise un grand concours de p�che!*Tu as d� en entendre parler, toute la ville participe!"; idsuiv=460; break;
        case 460 : texte = "Pour remporter le concours et gagner un prix sp�cial, il faut �tre le premier � p�cher 5 esp�ces de poissons diff�rentes."; idsuiv=461; break;
        case 461 : texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              OUI ?            non  "; idsuiv=463;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75; break;
        case 462 : texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              oui              NON ?"; idsuiv=464; break;
        case 463 : texte = "Tr�s bien, voici une canne � p�che, reviens lorsque tu auras p�ch� 5 poissons diff�rents."; break;
        case 464 : 
            texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              OUI ?            non  "; idsuiv=466; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 465 : texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              oui              NON ?"; idsuiv=467; break;
        case 466 : texte = "Bien, voici une canne � p�che, reviens lorsque tu auras p�ch� 5 poissons diff�rents."; break;
        case 467 : texte = "Et pour 2 Rubis ?**              OUI ?            non  "; idsuiv=469;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2) idsuiv=75; break;
        case 468 : texte = "Et pour 2 Rubis ?**              oui              NON ?"; idsuiv=470; break;
        case 469 : texte = "Bon, voici une canne � p�che, reviens lorsque tu auras p�ch� 5 poissons diff�rents."; break;
        case 470 : texte = "Pour 1 Rubis ?**              OUI ?            non  "; idsuiv=472;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<1) idsuiv=75; break;
        case 471 : texte = "Pour 1 Rubis ?**              oui              NON ?"; idsuiv=473; break;
        case 472 : texte = "Ok, voici une canne � p�che, reviens lorsque tu auras p�ch� 5 poissons diff�rents."; break;
        case 473 : texte = "Tu ne veux tout de m�me pas participer gratuitement ???*               SI ?            non  "; idsuiv=475; break;
        case 474 : texte = "Tu ne veux tout de m�me pas participer gratuitement ???*               si              NON ?"; idsuiv=476; break;
        case 475 : texte = "...*Voici une canne � p�che, reviens lorsque tu auras p�ch� 5 poissons diff�rents."; break;
        case 476 : texte = "Va-t-en, ennemi de la p�che!"; break;
        case 477 : texte = "Tu as obtenu une canne � p�che!*Utilise-la � un ponton, puis remonte la ligne en appuyant � nouveau sur Triangle lorsque la ligne bouge."; break;
        case 478 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) {id=487; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=5) {id=479; chercheText();break;}
            tmp = 5-gpJeu->getJoueur()->nbPoissons();
            os << tmp;
            if (tmp > 1) texte = "Encore "+os.str()+" poissons diff�rents � trouver, bonne chance!";
            else texte = "Plus qu'un poisson � trouver!"; break;
        case 479 : texte = "Tu as trouv� suffisamment de poissons ???*Tu dois �tre un super p�cheur!"; idsuiv=480; break;
        case 480 : texte = "Ca signifie que le concours de p�che est termin�, tu en es le vainqueur!"; idsuiv=481; break;
        case 481 : texte = "J'imagine que tu vas vouloir ton prix...*Pour te r�compenser d'avoir remporter le concours de p�che : *... ... ..."; idsuiv=482; break;
        case 482 : texte = "Je t'engage!"; idsuiv=483; break;
        case 483 : texte = "Il y a beaucoup d'autres esp�ces de poissons � Hyrule, je veux tous les r�pertorier par r�gion."; idsuiv=484; break;
        case 484 : texte = "Je te r�compenserai tous les 5 nouveaux poissons p�ch�s.*Tu peux d�sormais consulter la liste des poissons p�ch�s en appuyant sur D-Pad bas"; idsuiv=485; break;
        case 485 : texte = "Avec ta canne � p�che actuelle, tu ne pourras h�las p�cher que des petits poissons..."; break;
        case 486 : texte = "N'h�site pas � p�cher partout!*Chaque poisson p�ch� te redonne de la vie, l'avais-tu remarqu� ?"; break;
        case 487 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>1) {id=490; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=10) {id=488; chercheText();break;}
            tmp = 10-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons diff�rents � trouver avant la prochaine r�compense!";
            break;
        case 488 : texte = "Voici ta r�compense pour avoir trouv� 10 poissons diff�rents :"; break;
        case 489 : texte = "Tu as obtenu une meilleure canne � p�che!!!*Tu vas pouvoir attraper des poissons de taille moyenne."; break;
        case 490 : 
            if (gpJeu->getJoueur()->hasBouteille(2)) {id=492; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=15) {id=491; chercheText();break;}
            tmp = 15-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons diff�rents � trouver avant la prochaine r�compense!";
            break;
        case 491 : texte = "Voici ta r�compense pour avoir trouv� 15 poissons diff�rents :"; break;
        case 492 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>2) {id=495; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=20) {id=493; chercheText();break;}
            tmp = 20-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons diff�rents � trouver avant la prochaine r�compense!";
            break;
        case 493 : texte = "Voici ta r�compense pour avoir trouv� 20 poissons diff�rents :"; break;
        case 494 : texte = "Tu as obtenu la meilleure canne � p�che!!!*Tu vas pouvoir attraper des poissons de taille gigantesque!"; break;
        case 495 : 
            if (gpJeu->getJoueur()->getCoeur(27)) {id=497; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=25) {id=496; chercheText();break;}
            tmp = 25-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons diff�rents � trouver avant la prochaine r�compense!";
            break;
        case 496 : texte = "Voici ta r�compense pour avoir trouv� 25 poissons diff�rents :"; break;
        case 497 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)>1) {id=500; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=30) {id=498; chercheText();break;}
            tmp = 30-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons diff�rents � trouver avant la prochaine r�compense!";
            break;
        case 498 : texte = "Voici ta r�compense pour avoir trouv� tous les poissons diff�rents :"; break;
        case 499 : texte = "T'ES VIRE !!!!"; break;
        case 500 : texte = "Tous les poissons d'Hyrule sont enfin recens�s, mon guide du p�cheur est enfin fini..."; break;
        case 501 : texte = "Bonjour Link.*En temps que maire, je te souhaite la bienvenue au village des Mouettes."; 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) idsuiv=503; else idsuiv=502; break;
        case 502 : texte = "En ce moment un concours de p�che est organis� en ville, tout le monde ne parle que de �a... *Est-ce la raison de ta venue ?"; break;
        case 503 : texte = "Le concours de p�che �tant fini, le village des Mouettes est redevenu un lieu calme."; break;
        case 504 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>1) {id=511; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==1 
            && gpJeu->getJoueur()->getObjet()==7) {id=505; chercheText();break;}
            texte = "Je suis un p�cheur l�gendaire!*J'aime le c�t� bleu et brillant de la mer..."; 
            buffer = "Pourquoi je n'ai pas remport� le concours de p�che ?*Et bien euh... Ce genre de choses ne m'int�ressent pas.... Voil�."; break;
        case 505 : texte = "Une gemme bleue et brillante ?*Il me la faut!*Je te l'�change contre ma derni�re p�che!"; idsuiv=506; break;
        case 506 : texte = "Cette gemme bleue contre sa p�che, ok ?**              OUI ?            non  "; idsuiv=508; break;
        case 507 : texte = "Cette gemme bleue contre sa p�che, ok ?**              oui              NON ?"; idsuiv=509; break;
        case 508 : texte = "H�! H�! Tu fais une affaire petit."; buffer="Cette botte �tait remplie d'algues quand je l'ai p�ch�e, ce n'est pas courant hein ?"; break;
        case 509 : texte = "Tu es trop gentil, mais ne t'en fais pas pour moi, n'ai pas peur de m'arnaquer."; break;
        case 510 : texte = "Tu as troqu� la gemme bleue contre une vieille botte!*Bien jou�..."; break;
        case 511 : texte = "Si tu trouves d'autres gemmes bleues, ce sera un plaisir de faire � nouveau des affaires avec toi!"; break;
        case 512 : 
            if (!gpJeu->getJoueur()->hasObjet(O_CANNE)) texte = "De nos jours les jeunes n'�coutent plus les conseils des plus �g�s...*Je sens que ce concours de p�che va durer...";
            else {texte = "Autrefois j'�tais un p�cheur r�put�, veux-tu que je te donne quelques astuces ?"; idsuiv=513;} break;
        case 513 : texte = "A PROPOS DES ESPECES DE POISSONS ?*A propos des r�gions de p�che     *A propos des bonus                *Rien du tout                      "; idsuiv=517; break;
        case 514 : texte = "A propos des esp�ces de poissons  *A PROPOS DES REGIONS DE PECHE    ?*A propos des bonus                *Rien du tout                      "; idsuiv=518; break;
        case 515 : texte = "A propos des esp�ces de poissons  *A propos des r�gions de p�che     *A PROPOS DES BONUS               ?*Rien du tout                      "; idsuiv=519; break;
        case 516 : texte = "A propos des esp�ces de poissons  *A propos des r�gions de p�che     *A propos des bonus                *RIEN DU TOUT                     ?"; idsuiv=520; break;
        case 517 : texte = "On dit que les eaux d'Hyrule abritent pas moins de 30 esp�ces de poissons, mais ils ont chacun leur propre r�gion, tu ne les trouveras pas tous au m�me endroit."; break;
        case 518 : texte = "Il y a en Hyrule beaucoup d'endroits o� p�cher, mais seulement 6 r�gions distinctes. Pour trouver de nouveaux poissons tu devras aller p�cher � d'autres endroits."; 
            buffer="Si tu trouves un poisson d�j� connu ailleurs, c'est que tu es toujours dans la m�me r�gion de p�che."; break;
        case 519 : texte = "La p�che ne sert pas uniquement � se divertir, un poisson p�ch� te redonne de la vie. La quantit� de vie gagn�e d�pend du poisson p�ch�."; break;
        case 520 : texte = "Tsss... la jeunesse de nos jours..."; break;
        case 521 : 
            if (!gpJeu->getJoueur()->hasObjet(O_POISSONS)) texte = "J'ai pass� des heures � p�cher au bord du lac, et je n'ai pu trouver que 3 poissons diff�rents..."; 
            else texte = "Il fallait aller p�cher � diff�rents endroits pour trouver plus de 3 poissons ?*Si j'avais su..."; break;
        case 522 :
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=523; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE) {id=528; chercheText();break;}
            texte = "Je te sers quelque chose ?"; break;
        case 523 : texte = "Tu as besoin de l'aide du gars qui picole l�-bas ?*Je ne peux toutefois pas le laisser partir sans payer."; idsuiv=524; break;
        case 524 : texte = "Tu veux r�gler sa dette ? C'est 10 000 Rubis, ok ?*              OUI ?            non  "; idsuiv=75; break;
        case 525 : texte = "Tu veux r�gler sa dette ? C'est 10 000 Rubis, ok ?*              oui              NON ?"; idsuiv=526; break;
        case 526 : texte = "Evidemment..."; buffer="Je te propose autre chose : j'utilise habituellement un roc givre pour pr�parer des boissons fra�ches, mais je viens d'user le dernier laiss� par mes anc�tres..."; idsuiv=527; break;
        case 527 : texte = "Si tu m'apportes un nouveau roc givre, je veux bien effacer cette dette."; break;
        case 528 : 
            if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=529; chercheText();break;}
            texte = "Alors, tu ne trouves pas de roc givre ?"; break;
        case 529 : texte = "Tu as un roc givre ? Incroyable..."; idsuiv=530; break;
        case 530 : texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              OUI ?            non  "; idsuiv=533; break;
        case 531 : texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              oui              NON ?"; idsuiv=532; break;
        case 532 : texte = "Je comprends, ce ne sont pas tes affaires apr�s tout."; break;
        case 533 : texte = "Merci!*Comme promis, le vieil homme peut partir, il ne me doit plus rien."; break;
        case 534 : 
            if (gpJeu->getJoueur()->getAvancement()==PANCARTE_MINE_LUE) {id=535; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=537; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_BARMAN_SALOON) {id=538; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<0) {id=540; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=541; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==DETTE_PAYEE) {id=542; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==GARS_MINE_AIDE) {id=543; chercheText();break;}
            texte = "Laisse-moi boire en paix! Hic!"; break;
        case 535 : texte = "Tu viens de la mine ?*J'y travaille habituellement...*Avec l'apparition de monstres la mine a provisoirement ferm�..."; idsuiv=536; break;
        case 536 : texte = "Je pourrais t'aider � traverser la mine, mais le barman ne veut pas me laisser partir sans payer. Or je n'ai plus d'argent, je suis donc coinc� ici, et je bois pour passer le temps."; idsuiv=537; break;
        case 537 : texte = "Il faudrait vraiment que quelqu'un paie ma dette � ma place...*...*Hic!"; break;
        case 538 : texte = "Tu veux savoir o� trouver un roc givre ?*Mmm... j'ai entendu dire qu'un gars est arriv� � la cit� d'Hyrule derni�rement, et qu'il va ouvrir une boutique d'un nouveau genre..."; idsuiv=539; break;
        case 539 : texte = "Et bien il me semble que ce gars poss�de un roc givre."; break;
        case 540 : texte = "Va voir le gars qui tient une boutique bizarre dans la cit� d'Hyrule, il doit avoir un roc givre."; break;
        case 541 : texte = "Tu as un roc givre ???*Donne-le vite au barman, je promets de t'aider pour la mine!"; break;
        case 542 : texte = "Je suis libre d�sormais... Moi qui pensais faire la vaiselle jusqu'� la fin de la semaine!*Merci Link!"; idsuiv=543; break;
        case 543 : texte = "Tu peux aller � la mine, on se retrouve l�-bas.**Hic!"; break;
        case 544 : texte = "Bienvenue au saloon, fais comme chez toi Link!"; break;
        case 545 : texte = "Tant que la mine au Nord reste ferm�e, je n'ai rien d'autre � faire que de passer mon temps ici..."; break;
        case 546 : texte = "Pratiquement tous les hommes du village travaillent � la mine au Nord du village."; buffer="Ce matin des monstres sont apparus aux alentours et la mine a d� fermer."; break;
        case 547 : texte = "Le riz, les �pices et les olives sont les marchandises de base du troc � Hyrule, tu devrais toujours en avoir sur toi."; break;
        case 548 : texte = "Je suis le chef de la mine, et l'homme le plus puissant du village, alors inutile d'essayer de me prendre de haut, fiston."; break;
        case 549 : texte = "Je suis le chef du village... Mais en r�alit� le chef de la mine a beaucoup plus d'influence que moi, il a embauch� pratiquement tous les hommes du village."; break;
        case 550 : texte = "La banque est sous notre surveillance. RAS."; break;
        case 551 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=552;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=553;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=559;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=564;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis sp�cialis� en devises."; break;
        case 552 : texte = "Tu n'as rien qui m'int�resse, reviens si tu trouves de l'or, je t'en donnerai un bon prix."; break;
        case 553 : texte = "Tu poss�des des pi�ces d'or ? Avec une t�te de monstre dessus... Des Ganon d'or tu dis ?"; idsuiv=554; break;
        case 554 : texte = "C'est tr�s laid, mais l'or est r�cup�rable, alors voyons..."; idsuiv=555; break;
        case 555 : 
            int g;
            int gmax;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Rubis, ok ?**              OUI ?            non  "; idsuiv=558; break;
        case 556 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Rubis, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 557 : texte = "Ta bourse est pleine, reviens plus tard, je te rach�terai tout �a."; break;
        case 558 : texte = "Affaire conclue!"; break;
        case 559 : texte = "Tu poss�des des pi�ces d'or ? Je pensais que cette monnaie avait disparue depuis longtemps..."; idsuiv=560; break;
        case 560 : texte = "Je vais t'en donner un bon prix, alors voyons..."; idsuiv=561; break;
        case 561 : 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-4) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Pi�ce d'or contre "+os2.str()+" Rubis, ok ?**              OUI ?            non  "; idsuiv=563; break;
        case 562 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Pi�ce d'or contre "+os2.str()+" Rubis, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 563 : texte = "Affaire conclue!"; break;
        case 564 : texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Ganon d'or  *   - Rien  "; idsuiv=560; break;
        case 565 : texte = "Que veux-tu me vendre ?*   - Pi�ce d'or  *   - GANON D'OR ?*   - Rien  "; idsuiv=554; break;
        case 566 : texte = "Que veux-tu me vendre ?*   - Pi�ce d'or  *   - Ganon d'or  *   - RIEN ?"; idsuiv=76; break;
        case 567 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC2)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC3)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC4)==10) {id=574; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==7 
            && gpJeu->getJoueur()->getObjet()==3) {id=568; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==7 
            && gpJeu->getJoueur()->getObjet()==7) {id=575; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==8 
            && gpJeu->getJoueur()->getObjet()==11) {id=580; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==7 
            && gpJeu->getJoueur()->getObjet()==15) {id=585; chercheText();break;}
            texte = "Je suis ici pour construire un pont pour se rendre au Nord. Je suis s�r que �a servira un jour."; 
            buffer = "L'ennui c'est qu'il me manque des outils...*Comment vais-je faire ?"; break;
        case 568 : texte = "Ce marteau me plait...*Il me serait fort utile, veux-tu me le c�der contre un tr�sor l�gendaire que j'ai trouv� lorsque j'�tais explorateur ?"; idsuiv=569; break;
        case 569 : texte = "Ce marteau contre un tr�sor l�gendaire, ok ?**              OUI ?            non  "; idsuiv=571; break;
        case 570 : texte = "Ce marteau contre un tr�sor l�gendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 571 : texte = "Merci, prends ceci en �change :"; break;
        case 572 : texte = "Je sens que ce pont ne sera jamais termin�..."; break;
        case 573 : texte = "Tu as obtenu la fl�che de feu!*Cette fl�che enflamm�e utilise de la magie et d�livre une puissance incroyable!"; break;
        case 574 : texte = "Il semblerait que j'ai enfin tout ce dont j'avais besoin...*Je me motive, puis j'y vais!"; break;
        case 575 : texte = "C'est le plan d'un pont ?*J'en aurais vraiment besoin, veux-tu me le c�der contre un tr�sor l�gendaire que j'ai trouv� lorsque j'�tais explorateur ?"; idsuiv=576; break;
        case 576 : texte = "Ce plan contre un tr�sor l�gendaire, ok ?**              OUI ?            non  "; idsuiv=578; break;
        case 577 : texte = "Ce plan contre un tr�sor l�gendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 578 : texte = "Merci, prends ce cadeau en �change :"; break;
        case 579 : texte = "Tu as obtenu la fl�che de glace!*Cette fl�che givrante utilise de la magie et d�livre une puissance incroyable!"; break;
        case 580 : texte = "Tu as une scie ?*Je ne pourrais pas faire de pont sans, veux-tu me la c�der contre un tr�sor l�gendaire que j'ai trouv� lorsque j'�tais explorateur ?"; idsuiv=581; break;
        case 581 : texte = "Cette scie contre un tr�sor l�gendaire, ok ?**              OUI ?            non  "; idsuiv=583; break;
        case 582 : texte = "Cette scie contre un tr�sor l�gendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 583 : texte = "Merci, prends ce pr�sent en �change :"; break;
        case 584 : texte = "Tu as obtenu la fl�che de lumi�re!*Cette fl�che utilise beaucoup de magie et d�livre une puissance ultime!"; break;
        case 585 : texte = "Tu as un clou ?*Ca peut toujours servir, veux-tu me le c�der contre une babiole ?"; idsuiv=586; break;
        case 586 : texte = "Ce clou contre une babiole, ok ?**              OUI ?            non  "; idsuiv=588; break;
        case 587 : texte = "Ce clou contre une babiole, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 588 : texte = "Merci, prends donc �a en �change :"; break;
        case 589 : 
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {id=593; chercheText();break;}
            texte = "Bonjour Link, tu te souviens de moi ?"; idsuiv=590; break;
        case 590 : texte = "Des monstres sont apparus sur Hyrule aujourd'hui, alors une fois de plus je vais t�cher de tous les r�pertorier, et une fois de plus je compte sur ton aide."; idsuiv=591; break;
        case 591 : texte = "En appuyant sur D-Pad haut, tu peux voir les monstres d�j� r�pertori�s. Tu n'as qu'� vaincre un monstre pour qu'il soit ajout�."; idsuiv=592; break;
        case 592 : 
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<"10 pi�ces d'or"; break;
                case T_PRESENT : os<<"40 Rubis"; break;
                case T_FUTUR : os<<"20 Ganon d'or"; break;
            }
            texte = "Je te devrai "+os.str()+" � chaque monstre ajout�. Passe me voir r�guli�rement pour chercher ce que je te dois."; break;
        case 593 :
            g = gpJeu->getJoueur()->getSolde();
            if (g == 0) {id=595; chercheText();break;}
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Pi�ces d'or"; break;
                case T_PRESENT : os<<g<<" Rubis"; break;
                case T_FUTUR : os<<(g/2)<<" Ganon d'or"; break;
            }
            if (gpJeu->getEpoque() == T_FUTUR 
            && gpJeu->getJoueur()->getGanonMax() == 0) {id=1368; chercheText();break;}
            texte = "Je te dois "+os.str()+", veux-tu �tre pay� maintenant ?*              OUI ?            non  "; break;
        case 594 : 
            g = gpJeu->getJoueur()->getSolde();
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Pi�ces d'or"; break;
                case T_PRESENT : os<<g<<" Rubis"; break;
                case T_FUTUR : os<<(g/2)<<" Ganon d'or"; break;
            }
            texte = "Je te dois "+os.str()+", veux-tu �tre pay� maintenant ?*              oui              NON ?"; break;
        case 595 : texte="Ton compte est � 0, je t'ai tout donn�."; break;
        case 596 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=597;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=598;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=603;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=608;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis sp�cialis� en devises."; break;
        case 597 : texte = "Tu n'as rien qui m'int�resse, reviens si tu trouves de l'or ou des Rubis, je t'en donnerai un bon prix."; break;
        case 598 : texte = "Tu poss�des des Rubis ? Ca fait longtemps qu'ils ne sont plus utilis�s, mais leur valeur reste ind�niable..."; idsuiv=599; break;
        case 599 : texte = "Alors voyons..."; idsuiv=600; break;
        case 600 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()==gpJeu->getJoueur()->getGanonMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rubis contre "+os2.str()+" Ganon d'or, ok ?**              OUI ?            non  "; idsuiv=602; break;
        case 601 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rubis contre "+os2.str()+" Ganon d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 602 : texte = "Affaire conclue!"; break;
        case 603 : texte = "Tu poss�des des pi�ces d'or ? C'est incroyable que tu aies pu trouver une monnaie aussi ancienne!"; idsuiv=604; break;
        case 604 : texte = "Elles contiennent beaucoup d'or... *Alors voyons..."; idsuiv=605; break;
        case 605 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()>gpJeu->getJoueur()->getGanonMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Pi�ce d'or contre "+os2.str()+" Ganon d'or, ok ?**              OUI ?            non  "; idsuiv=607; break;
        case 606 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Pi�ce d'or contre "+os2.str()+" Ganon d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 607 : texte = "Affaire conclue!"; break;
        case 608 : texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Rubis  *   - Rien  "; idsuiv=604; break;
        case 609 : texte = "Que veux-tu me vendre ?*   - Pi�ce d'or  *   - RUBIS ?*   - Rien  "; idsuiv=599; break;
        case 610 : texte = "Que veux-tu me vendre ?*   - Pi�ce d'or  *   - Rubis  *   - RIEN ?"; idsuiv=76; break;
        case 611 : texte = "Ca faisait longtemps que je ne m'�tais pas autant amus�!"; break;
        case 612 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>6) {id=619; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==6 
            && gpJeu->getJoueur()->getObjet()==7) {id=613; chercheText();break;}
            texte = "L'un de mes anc�tres voulait construire un pont, mais il n'a r�ussit qu'� en faire le plan..."; 
            buffer = "Je viens d'une lign�e d'incapables, pas �tonnant que je sois si nul en tout... En plus je suis malade, et personne ne m'aime..."; break;
        case 613 : texte = "Tu as une corde ?*Donne-la-moi s'il te pla�t, je te donnerai l'h�ritage de ma famille, de toute fa�on je n'ai pas de descendants..."; idsuiv=614; break;
        case 614 : texte = "Cette corde contre son h�ritage, ok ?**              OUI ?            non  "; idsuiv=616; break;
        case 615 : texte = "Cette corde contre son h�ritage, ok ?**              oui              NON ?"; idsuiv=617; break;
        case 616 : texte = "Bon bah...*...Merci hein...*..."; break;
        case 617 : texte = "J'en �tais s�r, de toute fa�on on ne m'a jamais rien donn�..."; break;
        case 618 : texte = "Tu as troqu� la corde contre le plan d'un pont."; break;
        case 619 : texte = "...*J'aimerais �tre seul un moment..."; break;
        case 620 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=624; chercheText();break;}
            texte = "Bonjour, tu dois �tre Link, j'attendais ta venue."; idsuiv=621; break;
        case 621 : texte = "Je suis un descendant des 7 sages. Traqu� par les sbires de Ganon, j'ai d� fuir jusqu'ici."; idsuiv=622; break;
        case 622 : texte = "Te voir ici me redonne espoir, je vais aller prendre place dans la grotte du portail.*Prends ceci, �a devrait t'�tre utile."; break;
        case 623 : texte = "Tu as obtenu un poivron !"; break;
        case 624 : texte = "Bonne chance Link!"; break;
        case 625 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=635; chercheText();break;}
            texte = "Bienvenue Link, je t'attendais..."; idsuiv=626; break;
        case 626 : texte = "Tu dois avoir beaucoup de questions, laisse-moi y r�pondre."; idsuiv=627; break;
        case 627 : texte = "Nous sommes � Hyrule, mais dans ce qui n'est pour toi qu'un triste futur...*Le portail que tu as pris t'a permis de venir ici, pour �tre t�moin de ces sombres jours..."; idsuiv=628; break;
        case 628 : texte = "Tu veux savoir ce qui s'est pass� ? Ganon a attaqu� le ch�teau, plus fort que jamais, et tu as �t� vaincu."; idsuiv=629; break;
        case 629 : texte = "Avant son ex�cution, la princesse Zelda a r�ussi � faire parvenir son plan aux sages. Le vol de l'Ocarina du Temps fut selon elle le tournant de cette guerre, elle a donc demand� aux descendants des 7 sages de te remettre l'ocarina lorsque tu arriverais via le portail."; idsuiv=630; break;
        case 630 : texte = "Le jour est enfin venu puisque tu te tiens d�sormais face � moi.*Cependant... l'ocarina n'a jamais �t� retrouv�."; idsuiv=631; break;
        case 631 : texte = "Nous avons donc mis au point un autre plan. Nous allons t'envoyer dans le pass�, la nuit o� l'ocarina fut vol�, pour que tu surprennes le voleur."; idsuiv=632; break;
        case 632 : texte = "Nous ne sommes d�sormais plus que 3 descendants des sages, cherche et trouve les 2 autres ainsi que la cl� du temps, et nous t'ouvrirons le portail."; idsuiv=633; break;
        case 633 : texte = "Prends ceci, �a devrait t'aider dans tes recherches :"; break;
        case 634 : texte = "Tu as obtenu le grappin !*Sers-t'en pour franchir les pr�cipices!"; break;
        case 635 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=636; chercheText();break;}
            texte = "L'un d'entre eux se cache au fond d'un donjon, au milieu du lac."; break;
        case 636 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=637; chercheText();break;}
            texte = "Le dernier sage se cache vers les cascades."; break;
        case 637 : 
            if (gpJeu->getJoueur()->hasObjet(O_CLE_TEMPS)) {id=638; chercheText();break;}
            texte = "La cl� du temps se trouve au fond de la Grande Pyramide."; break;
        case 638 : 
            if (gpJeu->getJoueur()->getAvancement()>SAGES_GROTTE) {id=639; chercheText();break;}
            texte = "Les sages sont dans la grotte, la cl� du temps est en ta possession...*Tr�s bien, retrouvons-nous � la grotte du portail, le temps est venu."; break;
        case 639 :
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=640; chercheText();break;}
            texte = "Dans le temple du Temps se trouve un air qui, jou� par l'ocarina, te ram�nera � ton �poque."; break;
        case 640 : texte = "Bonne chance Link, nous comptons tous sur toi."; break;
        case 641 : texte = "10 fl�ches pour 10 Ganon d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75; break;
        case 642 : texte = "10 fl�ches pour 10 Ganon d'or ?**              oui              NON ?"; break;
        case 643 : texte = "5 bombes pour 15 Ganon d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<15) idsuiv=75; break;
        case 644 : texte = "5 bombes pour 15 Ganon d'or ?**              oui              NON ?"; break;
        case 645 : texte = "Un petit coeur pour 4 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<4) idsuiv=75; break;
        case 646 : texte = "Un petit coeur pour 4 Ganon d'or ?**              oui              NON ?"; break;
        case 647 : texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<8) idsuiv=75; break;
        case 648 : texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              oui              NON ?"; break;
        case 649 : texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<16) idsuiv=75; break;
        case 650 : texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              oui              NON ?"; break;
        case 651 : 
            if (gpJeu->getJoueur()->getGanonMax()>0) {id=652; chercheText(); break;}
            texte = "Chaque seconde est une goutte de plus dans la cafeti�re, tu me fais perdre mon temps."; break;
        case 652 :
            if (gpJeu->getJoueur()->getCafe()>-1) {id=653; chercheText(); break;}
            texte = "Tu veux bosser pour moi ? La valeur d'un homme se mesure � sa charge de travail, c'est ce que je dis toujours !"; idsuiv=653; break;
        case 653 : 
            if (gpJeu->getJoueur()->getChargeCafe()==-1 
            && gpJeu->getMonde()->motifValue(6*16,8*16)==1005) {id=655; chercheText(); break;}
            if (gpJeu->getJoueur()->getCafe()>=17) {id=672; chercheText(); break;}
            texte = "Cours sur le tapis roulant pour charger la dynamo, puis marche sur l'interrupteur. Cela mettra en marche la cafeti�re. Apr�s �a viens me voir, et tu auras de l'argent."; idsuiv=654; break;
        case 654 : texte = "Je ne te demande pas si tu es pr�t, la pr�paration est l'ultime refuge des faibles."; break;
        case 655 : 
            if (gpJeu->getJoueur()->getCafe()>1) {
                id=654+gpJeu->getJoueur()->getCafe(); chercheText(); break;}
            texte = "Je ne bois jamais plus de 17 tasses de caf� par jour.*Mais la premi�re est toujours la meilleure."; break;
        case 656 : texte = "Plus noir qu'une nuit sans lune, plus br�lant et amer que l'enfer... *Ca, c'est du caf�."; break;
        case 657 : texte = "Visiblement, on va en prendre une autre pour la route."; break;
        case 658 : texte = "Au fait, ne mets pas de sel dans ton caf�. J'ai essay�, c'est d�go�tant."; break;
        case 659 : texte = "Ce caf�... C'est un m�lange sp�cial que j'ai appel� Godot N107. J'h�site entre r�duire son acidit� et diminuer son amertume... C'est tout ce que j'ai en t�te pour l'instant..."; break;
        case 660 : texte = "Ah... !*Ma 6�me tasse de caf� me regarde d'un air froid."; break;
        case 661 : texte = "M�lange Godot N102...*... Mon pr�f�r�."; break;
        case 662 : texte = "Ah... ! Ce m�lange...*Du m�lange Godot N107...*Il est peut-�tre un peu trop amer en fin de compte !"; break;
        case 663 : texte = "...*Aaah, amer !"; break;
        case 664 : texte = "Les faibles se font emporter par le flot du destin, les forts arrivent � l'ingurgiter. *Ah... !*Le destin a, aujourd'hui encore, un go�t d'amertume."; break;
        case 665 : texte = "Ma 11�me tasse...*Je me suis promis de ne pas d�passer 17 tasses par jour, j'ai donc encore de la marge..."; break;
        case 666 : texte = "Une petite goutte de lait suffit � d�truire la noire magie du caf� !"; break;
        case 667 : texte = "... Quelle amertume.*Tu apprendras � appr�cier l'amertume quand tu seras plus grand."; break;
        case 668 : texte = "Tu connais ma r�gle d'or ?*Jeter la tasse de caf� qui est imbuvable et en prendre une autre."; break;
        case 669 : texte = "Ah !*En ce cas, le moment est bien choisi... pour une autre tasse de magie noire !"; break;
        case 670 : texte = "Deux minutes ne suffisent pas pour extraire tout l'ar�me d'un bon arabica..."; break;
        case 671 : texte = "La 17�me et derni�re tasse.*L'heure est venue de classer cette affaire."; break;
        case 672 : 
            if (gpJeu->getJoueur()->getGemme(173)) {id=673; chercheText(); break;}
            texte = "J'ai bu mes 17 tasses, voil� une r�compense :"; break;
        case 673 : texte = "Tu as encore besoin d'argent ? En voil�..."; break;
        case 674 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'�nergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=675; break;
        case 675 : texte = "Que d�sires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=678; break;
        case 676 : texte = "Que d�sires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=680; break;
        case 677 : texte = "Que d�sires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 678 : texte = "Une potion rouge pour 40 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<40) idsuiv=75; break;
        case 679 : texte = "Une potion rouge pour 40 Ganon d'or ?**              oui              NON ?"; break;
        case 680 : texte = "Une potion verte pour 25 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<25) idsuiv=75; break;
        case 681 : texte = "Une potion verte pour 25 Ganon d'or ?**              oui              NON ?"; break;
        case 682 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=683; chercheText();break;}
            texte = "Ma famille n'a connu que malchance sur malchance depuis des si�cles...*M�me que je le voudrais, je n'aurai rien � t'offrir."; break;
        case 683 :
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>=4) {id=685; chercheText();break;}
            texte = "Je suis l'homme le plus chanceux du pays."; buffer = "Tu ne me crois pas ?*Prends ce tr�sor que j'ai trouv� ce matin en me promenant, j'en trouverai sans doute un nouveau demain!"; break;
        case 684 : texte = "Tu obtiens un bijou pr�cieux !"; break;
        case 685 : texte = "C'est curieux, en te donnant ce bijou j'ai l'�trange impression de r�gler une vieille dette familiale..."; break;
        case 686 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>4) {id=693; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==4 
            && gpJeu->getJoueur()->getObjet()==15) {id=687; chercheText();break;}
            texte = "Je suis le p�tissier le plus r�put� du pays."; buffer = "Malheureusement je n'ai plus rien en stock, on ne trouve plus grand chose de sucr� depuis longtemps..."; break;
        case 687 : texte = "Tu as de la confiture ???*Je croyais que les derni�res �taient p�rim�es depuis des lustres! Donne-la-moi, contre ma r�serve sp�ciale petit d�j'!"; idsuiv=688; break;
        case 688 : texte = "Cette confiture contre sa r�serve, ok ?**              OUI ?            non  "; idsuiv=690; break;
        case 689 : texte = "Cette confiture contre sa r�serve, ok ?**              oui              NON ?"; idsuiv=691; break;
        case 690 : texte = "Je sens que je vais me r�galer demain moi! *Voil� ce que je gardais de c�t� :"; break;
        case 691 : texte = "Dans ce cas pourquoi me l'as-tu pr�sent� ? *Frimeur..."; break;
        case 692 : texte = "Tu as troqu� la confiture contre un croissant."; break;
        case 693 : texte = "T�t ou tard, il va bien falloir que je change de m�tier tout de m�me..."; break;
        case 694 :
            if (gpJeu->getJoueur()->getGanonMax() > 0) {id=696; chercheText();break;}
            texte = "Tu as l'air encore plus fauch� que moi...*Tu devrais voir le gars de la maison du caf�, il cherche un employ�."; buffer = "Prends �galement �a, tu en auras besoin :"; break;
        case 695 : texte = "Tu as obtenu une bourse pouvant contenir 99 Ganon d'or !"; break;
        case 696 : texte = "Alors, comment se portent tes finances ?"; break;
        case 697 : 
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=698;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=699;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=704;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=709;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis sp�cialis� en devises."; break;
        case 698 : texte = "Tu n'as rien qui m'int�resse, reviens si tu trouves des devises pr�cieuses, je t'en donnerai un bon prix."; break;
        case 699 : texte = "Ce sont des Rubis dis-tu ? C'est assez curieux."; idsuiv=700; break;
        case 700 : texte = "Ca a l'air pr�cieux, alors voyons..."; idsuiv=701; break;
        case 701 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rubis contre "+os2.str()+" Pi�ce d'or, ok ?**              OUI ?            non  "; idsuiv=703; break;
        case 702 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rubis contre "+os2.str()+" Pi�ce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 703 : texte = "Affaire conclue!"; break;
        case 704 : texte = "Tu poss�des de l'or ? Avec une t�te de monstre dessus... Des Ganon d'or tu dis ?"; idsuiv=705; break;
        case 705 : texte = "C'est tr�s laid, mais l'or est r�cup�rable, alors voyons..."; idsuiv=706; break;
        case 706 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Pi�ce d'or, ok ?**              OUI ?            non  "; idsuiv=708; break;
        case 707 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Pi�ce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 708 : texte = "Affaire conclue!"; break;
        case 709 : texte = "Que veux-tu me vendre ?*   - RUBIS ?*   - Ganon d'or  *   - Rien  "; idsuiv=700; break;
        case 710 : texte = "Que veux-tu me vendre ?*   - Rubis  *   - GANON D'OR ?*   - Rien  "; idsuiv=705; break;
        case 711 : texte = "Que veux-tu me vendre ?*   - Rubis  *   - Ganon d'or  *   - RIEN ?"; idsuiv=76; break;
        case 712 :
            if (gpJeu->getJoueur()->getCoffre(15,22)) {id=717; chercheText();break;}
            texte = "Bonjour Link, je t'attendais."; idsuiv=713; break;
        case 713 : texte = "Je suis le chef des 7 sages, mais aussi le plus puissant d'entre eux. Je t'ai vu dans mes songes, ainsi qu'un bien triste avenir..."; idsuiv=714; break;
        case 714 : texte = "Ta pr�sence ici semble indiquer que j'ai r�ussi... Au moins partiellement..."; idsuiv=715; break;
        case 715 : texte = "Je suis celui qui a cr�� le portail vers le futur, dans le but que tu sois t�moin de l'objet de mes visions."; idsuiv=716; break;
        case 716 : texte = "J'ai �galement construit le temple du Temps avec les autres sages, pour te permettre de voyager � ta guise entre les �poques."; idsuiv=717; break;
        case 717 : texte = "D�sormais c'est � toi de jouer. Trouve les 7 cristaux magiques qui t'ouvriront l'acc�s au l�gendaire temple des D�esses, et soit le premier � t'emparer de la Triforce!"; idsuiv=718; break;
        case 718 : texte = "Puisse son chemin mener le h�ros � la Triforce."; break;
        case 719 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>2
            && gpJeu->getJoueur()->hasObjet(O_TROC2)>3
            && gpJeu->getJoueur()->hasObjet(O_TROC3)>3) {id=726; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==2 
            && gpJeu->getJoueur()->getObjet()==3) {id=720; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==3 
            && gpJeu->getJoueur()->getObjet()==7) {id=727; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==3 
            && gpJeu->getJoueur()->getObjet()==11) {id=733; chercheText();break;}
            texte = "Ne te fie pas � ma taille, je suis un forgeron de premier ordre."; 
            buffer = "Cependant je dois avouer que je viens d'emm�nager, et je n'�tais pas de taille � d�m�nager ma forge jusqu'ici... Donc je n'ai plus rien."; break;
        case 720 : texte = "Tu as transport� une enclume avec toi ???*T'es b�te ou quoi ?"; buffer = "Je peux t'en d�lester si tu veux, je pourrais en avoir besoin. *Je te donnerai m�me une petite r�compense pour l'effort."; idsuiv=721; break;
        case 721 : texte = "Cette enclume contre une r�compense, ok ?**              OUI ?            non  "; idsuiv=723; break;
        case 722 : texte = "Cette enclume contre une r�compense, ok ?**              oui              NON ?"; idsuiv=724; break;
        case 723 : texte = "Merci, voici un fer � cheval que j'avais r�alis� il y a quelques temps :"; break;
        case 724 : texte = "Je disais �a pour t'aider..."; break;
        case 725 : texte = "Tu as obtenu un fer � cheval!"; break;
        case 726 : texte = "Avec tout ce que tu m'as apport�, je vais pouvoir r�ouvrir ma forge!"; break;
        case 727 : texte = "C'est un beau marteau que tu as l�...*Il pourrait faire l'affaire pour ma forge... Tu me le c�derais ? Je te r�compenserai par une de mes cr�ations."; idsuiv=728; break;
        case 728 : texte = "Ce marteau contre une r�compense, ok ?**              OUI ?            non  "; idsuiv=730; break;
        case 729 : texte = "Ce marteau contre une r�compense, ok ?**              oui              NON ?"; idsuiv=731; break;
        case 730 : texte = "Merci, voici une de mes plus belles cr�ations :"; break;
        case 731 : texte = "Comme si ce marteau pouvait t'�tre utile..."; break;
        case 732 : texte = "Tu as obtenu une clochette!"; break;
        case 733 : texte = "Tu as de la poudre d'or ?*J'en aurai besoin pour forger � nouveau des objets exceptionnels, tu me la donnes contre une r�compense exceptionnelle ?"; idsuiv=734; break;
        case 734 : texte = "La poudre d'or contre une r�compense, ok ?**              OUI ?            non  "; idsuiv=736; break;
        case 735 : texte = "La poudre d'or contre une r�compense, ok ?**              oui              NON ?"; idsuiv=737; break;
        case 736 : texte = "Merci, prends ce miroir magique en �change! *Il a �t� envo�t� par les sages et poss�de un pouvoir myst�rieux..."; break;
        case 737 : texte = "Je t'aurais largement d�dommag� pourtant..."; break;
        case 738 : texte = "Tu as obtenu le miroir magique!"; break;
        case 739 : 
            if (gpJeu->getJoueur()->getEpee()>2) {id=748; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==0) {id=745; chercheText();break;}
            texte = "Ton �p�e est impressionnante... Je devrais toutefois pouvoir l'am�liorer..."; idsuiv=740; break;
        case 740 : texte = "Veux-tu que je reforge ton �p�e ?**              OUI ?            non  "; idsuiv=742; break;
        case 741 : texte = "Veux-tu que je reforge ton �p�e ?**              oui              NON ?"; idsuiv=743; break;
        case 742 : texte = "Laisse-moi ton �p�e dans ce cas, ce ne sera pas long."; break;
        case 743 : texte = "Dommage, ton �p�e est vraiment fascinante..."; break;
        case 744 : texte = "Tu as confi� Excalibur."; break;
        case 745 : texte = "Ce ne sera pas long, ne t'inqui�te pas."; break;
        case 746 :
            if (gpJeu->getJoueur()->getEpee()) {id=748; chercheText();break;}
            texte = "C'est pr�t, voici ton �p�e :"; break;
        case 747 : texte = "Excalibur a �t� reforg�e! Sa puissance a bien augment�!"; break;
        case 748 : texte = "Un jour, je forgerai une �p�e aussi belle que la tienne, foi de forgeron!"; break;
        case 749 : texte = "Tu ne devrais pas t'�loigner du village par ce temps..."; break;
        case 750 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "10 fl�ches pour 5 Pi�ces d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<5) idsuiv=75; break;
        case 751 : texte = "10 fl�ches pour 5 Pi�ces d'or ?**              oui              NON ?"; break;
        case 752 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "5 bombes pour 10 Pi�ces d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 753 : texte = "5 bombes pour 10 Pi�ces d'or ?**              oui              NON ?"; break;
        case 754 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Un petit coeur pour 1 Pi�ce d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 755 : texte = "Un petit coeur pour 1 Pi�ce d'or ?**              oui              NON ?"; break;
        case 756 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Une petite fiole de magie pour 3 Pi�ces d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<3) idsuiv=75; break;
        case 757 : texte = "Une petite fiole de magie pour 3 Pi�ces d'or ? *              oui              NON ?"; break;
        case 758 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Une grande fiole de magie pour 6 Pi�ces d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<6) idsuiv=75; break;
        case 759 : texte = "Une grande fiole de magie pour 6 Pi�ces d'or ? *              oui              NON ?"; break;
        case 760 : texte = "Tu as trouv� le livre de Mudora!*Tu comprends d�sormais le Hylien ancien !"; break;
        case 761 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Bonjour, je suis le chef de ce village. *N'�coute pas les rumeurs comme quoi ce village serait menac�, et passe du bon temps parmi nous."; break;
        case 762 : texte = "La neige semble s'�tre arr�t�e..."; break;
        case 763 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'�nergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=764; break;
        case 764 : texte = "Que d�sires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=767; break;
        case 765 : texte = "Que d�sires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=769; break;
        case 766 : texte = "Que d�sires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 767 : texte = "Une potion rouge pour 15 Pi�ces d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<15) idsuiv=75; break;
        case 768 : texte = "Une potion rouge pour 15 Pi�ces d'or ?**              oui              NON ?"; break;
        case 769 : texte = "Une potion verte pour 10 Pi�ces d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 770 : texte = "Une potion verte pour 10 Pi�ces d'or ?**              oui              NON ?"; break;
        case 771 : texte = "Tu as l'air bien pauvre, tu n'as m�me pas de bourse sur toi ?*Prends donc celle-l� :"; break;
        case 772 : texte = "Tu as obtenu une bourse pouvant contenir 99 pi�ces d'or !"; break;
        case 773 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Bonjour, je suis un des 7 sages, de passage dans le coin."; idsuiv=774; break; 
        case 774 :
            texte ="Le livre de Mudora a �t� envo�t� pour permettre � quiconque le poss�de de parler couramment notre langue.";
            buffer = "Tu dois venir de loin pour ne pas parler hylien... Garde ce livre, tu en auras besoin."; break;
        case 775 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Salut mon gars, moi c'est Ganondorf, si tu d�couvres quoi que ce soit sur les cristaux magiques, tu viens m'en parler, �a marche ?"; break;
        case 776 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je suis le chef des chevaliers hyliens. *Si tu ne veux pas de soucis tiens-toi � carreau, prends exemple sur Ganondorf, c'est un bon gars."; break;
        case 777 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Ce Ganondorf n'arr�te pas de nous payer � boire... *C'est vraiment un type bien..."; break;
        case 778 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>5) {id=785; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==5 
            && gpJeu->getJoueur()->getObjet()==15) {id=779; chercheText();break;}
            texte = "C'est bien beau de boire... mais quand est-ce qu'on mange ?"; break;
        case 779 : texte = "Ne me dis rien... A l'odeur... C'est un croissant !*Donne-le-moi, en �change de mon amiti� �ternelle!"; idsuiv=780; break;
        case 780 : texte = "Ce croissant contre son amiti�, ok ?**              OUI ?            non  "; idsuiv=782; break;
        case 781 : texte = "Ce croissant contre son amiti�, ok ?**              oui              NON ?"; idsuiv=783; break;
        case 782 : texte = "Merci!!!*Prends ce cadeau en �change, ce sera le symbole de notre amiti�!"; break;
        case 783 : texte = "... Tu d�clares la guerre aux chevaliers hyliens ???*T'es fou ou quoi ???"; break;
        case 784 : texte = "Tu as troqu� le croissant contre une bi�re."; break;
        case 785 : texte = "Salut mon pote!*Tu viens boire un coup avec nous ?"; break;
        case 786 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Si tu veux qu'un chevalier hylien te d�voile une info top secr�te, il faut lui payer � boire. C'est notre r�gle."; break;
        case 787 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->getCoffre(15,23)<3) {id=788; chercheText(); break;}
            texte = "Tu connais d�j� toutes mes infos...*Hic!"; break;
        case 788 : 
            texte = "J'ai plein d'infos secr�tes connues de nous seuls (et de Ganondorf). Un verre de bi�re co�te 1 pi�ce d'or, affaire conclue ?"; idsuiv=789; break;
        case 789 : 
            texte = "Une info pour 1 pi�ce d'or, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 790 : texte = "Une info pour 1 pi�ce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 791 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>0) {id=792; chercheText(); break;}
            texte = "Les chevaliers hyliens auraient �t� fond�s pour prot�ger le l�gendaire temple des D�esses... Temple qui cacherait une relique toute puissante appel�e Triforce..."; break;
        case 792 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>1) {id=793; chercheText(); break;}
            texte = "Pour ouvrir l'acc�s au temple des D�esses, il faut se rendre sur la terre sacr�e, au nord d'ici, et se tenir sur le symbole de la Triforce avec les 7 cristaux magiques en poche."; break;
        case 793 : texte = "Les 7 cristaux magiques sont cach�s un peu partout dans Hyrule... Et, garde �a pour toi, l'un d'entre eux est en possession des l�gendaires chevaliers hyliens!"; break;
        case 794 : texte = "Notre chef l'a poursuivi en bas..."; break;
        case 795 : texte = "Quelle force... nous avons �t� balay�s si vite..."; break;
        case 796 : texte = "Il est... au sous-sol...*Soit prudent... ... mon ami."; break;
        case 797 : texte = "Il est trop fort... Le chef ne tiendra pas longtemps...*Va l'aider, je t'en prie..."; break;
        case 798 : texte = "Il... faut l'arr�ter..."; break;
        case 799 : texte = "Tu comptes �galement te mettre sur mon chemin ? Alors en garde!"; break;
        case 800 : texte = "J'ai �chou�...*Pardonnez-moi ma�tre..."; break;
        case 801 : texte = "Merci de ton aide Link, sans toi Ganondorf se serait empar� du cristal..."; idsuiv=802; break;
        case 802 : texte = "L'ordre des chevaliers a �t� fond� pour garder l'acc�s au temple des D�esses, nous avions donc pour mission de cacher ce cristal. Sans celui-ci, les 6 autres ne servent � rien."; idsuiv=803; break;
        case 803 : texte = "H�las, avec le temps, l'ordre s'est affaibli. Et aujourd'hui, nous avons �chou�."; idsuiv=804; break;
        case 804 : texte = "Garde le cristal, tu es plus � m�me de le d�fendre que nous..."; idsuiv=805; break;
        case 805 : texte = "Quant � Ganondorf... Jamais nous n'aurions pu deviner qu'il allait nous trahir... Il �tait pratiquement l'un des n�tres..."; idsuiv=806; break;
        case 806 : texte = "Il a �t� conduit � la prison de haute s�curit�, un peu au Nord d'ici... *Il ne devrait plus causer de soucis d�sormais..."; break;
        case 807 : 
            if (gpJeu->getJoueur()->getGemme(178)) {id=816; chercheText(); break;}
            texte = "J'ai �chou� contre Ganondorf, mais ne me sous-estime pas pour autant. Je suis l'homme qui a vaincu 100 loups."; idsuiv=808; break;
        case 808 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=1) {id=809; chercheText(); break;}
            texte = "Tu n'as battu aucun loup ???*Mais t'es un l�che!"; break;
        case 809 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=2) {id=810; chercheText(); break;}
            texte = "Tu n'as battu qu'un seul loup ???*Mais t'es un faible!"; break;
        case 810 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=50) {id=811; chercheText(); break;}
            os << g;
            texte = "Tu as battu seulement "+os.str()+" loups ?*C'est pas terrible..."; break;
        case 811 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=80) {id=812; chercheText(); break;}
            os << g;
            texte = "Tu as battu "+os.str()+" loups ?*C'est pas mal..."; break;
        case 812 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=100) {id=813; chercheText(); break;}
            os << g;
            texte = "Tu as battu "+os.str()+" loups ?*C'est plut�t impressionnant..."; break;
        case 813 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>100) {id=814; chercheText(); break;}
            texte = "Tu as battu 100 loups ?*Autant que moi... c'est dur � croire..."; break;
        case 814 : 
            texte = "Tu as battu plus de 100 loups ???*Incroyable..."; idsuiv=815; break;
        case 815 : texte = "Tu as bien m�rit� cette r�compense :"; break;
        case 816 : texte = "Il est temps pour moi de reprendre l'entra�nement..."; break;
        case 817 : texte = "Je vais changer de coiffure."; break;
        case 818 : texte = "Je vais commencer un r�gime."; break;
        case 819 : texte = "Je ne vendrai plus d'infos top secr�tes."; break;
        case 820 : texte = "Je ne passerai plus mes journ�es � la taverne."; break;
        case 821 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>5) {id=828; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==5 
            && gpJeu->getJoueur()->getObjet()==7) {id=822; chercheText();break;}
            texte = "J'ai cass� ma derni�re hache... Alors je joue au pendu pour tuer le temps, mais c'est pas pareil..."; break;
        case 822 : texte = "Tu as une hache pour moi ???*Donne-la-moi! Je te l'�change contre une corde tout aussi efficace!"; idsuiv=823; break;
        case 823 : texte = "Cette hache contre une corde, ok ?**              OUI ?            non  "; idsuiv=825; break;
        case 824 : texte = "Cette hache contre une corde, ok ?**              oui              NON ?"; idsuiv=826; break;
        case 825 : texte = "Je suis tellement �mu...*Voil� pour toi :"; break;
        case 826 : texte = "...*Ca devrait �tre passible de la peine de mort..."; break;
        case 827 : texte = "Tu as troqu� la hache contre une corde."; break;
        case 828 : texte = "Je suis impatient d'essayer cette hache!"; break;
        case 829 : texte = "Bonjour, je suis le chef de ce village."; idsuiv=830; break;
        case 830 : texte = "Le village des Mouettes est le paradis pour les touristes, mais aussi l'enfer pour les brigands."; buffer = "Savais-tu qu'un c�l�bre pirate avait �t� captur� lors de son passage dans cette ville ?"; break;
        case 831 : texte = "Tu as trouv� un marteau!"; break;
        case 832 : 
            if (gpJeu->getJoueur()->getCoffre(15,26)) {id=839; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==6 
            && gpJeu->getJoueur()->getObjet()==3) {id=833; chercheText();break;}
            texte = "Mon �poux est garde � la prison.*C'est un travail � temps plein alors on ne se voit pas beaucoup..."; break;
        case 833 : texte = "???*Qu'as-tu l� ???*Laisse-moi examiner �a!"; idsuiv=834; break;
        case 834 : texte = "Lui laisser l'alliance, ok ?**              OUI ?            non  "; idsuiv=836; break;
        case 835 : texte = "Lui laisser l'alliance, ok ?**              oui              NON ?"; idsuiv=837; break;
        case 836 : texte = "L'alliance de mon mari!*Ne me dis pas qu'il est retourn� LA voir!!!"; break;
        case 837 : texte = "...*Ca me semble tr�s louche...*Laisse-moi voir �a!"; idsuiv=834; break;
        case 838 : texte = "Tu as troqu� l'alliance contre rien."; break;
        case 839 : texte = "Pousse-toi de mon chemin!"; break;
        case 840 : texte = "Ne va pas � la r�serve, je n'y ai pas fait le m�nage!"; break;
        case 841 : texte = "Un c�l�bre pirate nomm� Ganon D. Roger fut captur� dans cette ville il y a bien longtemps...";
            buffer = "D'apr�s des rumeurs, un descendant de ce pirate serait � Hyrule en ce moment..."; break;
        case 842 : texte = "Tu es ici dans la demeure des 7 sages.*Ce lieu est celui de la m�ditation et de la connaissance."; break;
        case 843 : texte = "Notre chef, le plus puissant des 7 sages, vient rarement ici. Il pr�f�re rester � m�diter dans sa maison au Sud du village."; break;
        case 844 : texte = "Il y a quelques ann�es, nous �tions 8 sages. L'un d'entre nous, Agahnim, pensait qu'il �tait de notre devoir de r�cup�rer la Triforce et de s'en servir dans l'int�r�t de tous."; idsuiv=845; break;
        case 845 : texte = "Notre chef s'y opposa cat�goriquement. Il disait qu'un tel pouvoir ne devait pas tomber entre les mains des hommes, que les cons�quences pourraient �tre terribles..."; idsuiv=846; break;
        case 846 : texte = "Apr�s ce diff�rent, Agahnim quitta l'ordre. Mais derni�rement, il a r�apparu, dot� d'�tranges pouvoirs...*Nous ne savons h�las pas ce qu'il a en t�te."; break;
        case 847 : texte = "Un pirate l�gendaire est venu en Hyrule il y a longtemps. Il fut captur� � la suite d'un long combat face aux chevaliers hyliens de l'�poque."; idsuiv=848; break;
        case 848 : texte = "Le jour de son ex�cution publique, un homme dans la foule lui demanda o� il avait cach� son tr�sor. Le pirate expliqua l'avoir cach� dans 4 temples d'Hyrule."; idsuiv=849; break;
        case 849 : texte = "Suite � cette d�claration, de nombreux hommes partir � la recherche de ces tr�sors, mais aucun ne revint jamais..."; break;
        case 850 : texte = "As-tu rencontr� un certain Ganondorf ? *Lorsqu'il �tait encore enfant, il faillit finir dans l'estomac d'un loup, mais fut sauv� par un ancien membre de notre ordre."; idsuiv=851; break; 
        case 851 : texte = "Depuis il consid�re son sauveur comme son mentor."; break;
        case 852 : texte = "Notre chef nous demanda d'unir nos pouvoirs pour cr�er un temple tr�s particulier � l'Est d'ici. Selon lui ce temple permettra de sauver le monde..."; break;
        case 853 : 
            if (gpJeu->getJoueur()->getGemme(182)) {id=854; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>0) {id=855; chercheText();break;}
            texte = "La montagne au Nord du village cache un temple. Au fond de ce temple se trouve un tr�sor inestimable. Mais... c'est bien trop dangereux d'y aller."; break;
        case 854 : texte = "Je n'en reviens toujours pas que tu aies pu r�cup�rer ce tr�sor..."; break;
        case 855 : texte = "QUOI ??? TU AS TROUVE LE TRESOR DU TEMPLE !!!"; idsuiv=856; break;
        case 856 : texte = "Incroyable... prends �a, je tiens � te r�compenser pour ton exploit!"; break;
        case 857 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>4) {id=864; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==4 
            && gpJeu->getJoueur()->getObjet()==3) {id=858; chercheText();break;}
            texte = "Ca fait longtemps qu'IL ne m'a rien offert..."; break;
        case 858 : texte = "Tu as un bijou pour moi ?*Ca vient de LUI n'est-ce pas ?*Oui �a ne peut venir que de LUI!"; idsuiv=859; break;
        case 859 : texte = "Donner ce bijou ?**              OUI ?            non  "; idsuiv=861; break;
        case 860 : texte = "Donner ce bijou ?**              oui              NON ?"; idsuiv=862; break;
        case 861 : texte = "C'est tellement gentil de sa part...*Peux-tu aller lui porter cette lettre � la prison s'il te pla�t ?"; break;
        case 862 : texte = "...*Je LUI dirai !"; break;
        case 863 : texte = "Tu as troqu� le bijou contre une lettre."; break;
        case 864 : texte = "Hi! Hi! Hi!"; break;
        case 865 : texte = "Je suis le chef du village et euh... de toute fa�on ce sont les sages qui commandent ici..."; break;
        case 866 :
            if (gpJeu->getJoueur()->getCoffre(15,27)==12) {id=886; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(15,27)) {id=868; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=867; chercheText();break;}
            texte = "Nous sommes ferm�s au public."; break;
        case 867 : texte = "Nous t'avons longtemps attendu...*Prends le temps de visiter mon op�ra..."; break;
        case 868 : texte = "Cet op�ra a une longue histoire, prends le temps de la d�couvrir..."; break;
        case 869 : texte = "Bienvenue � toi visiteur, laisse-moi te conter l'histoire de cet endroit."; buffer="Je suis le fondateur de cet op�ra, mais autrefois je n'�tais qu'un simple voleur."; break;
        case 870 : texte = "Un jour, un cambriolage a mal tourn�, les chevaliers hyliens qui patrouillaient pr�s de la taverne me sont tomb�s dessus. Je fus condamn� et emmen� en prison."; break;
        case 871 : texte = "En prison, je trouvai un vieux cr�ne sous ma couchette. Je m'en servis alors comme accessoire pour r�citer des tirades, au grand bonheur de mon compagnon de cellule."; idsuiv=872; break;
        case 872 : texte = "C'est donc en prison que ma vocation pour le th��tre, puis pour l'op�ra, d�buta."; break;
        case 873 : texte = "Peu de temps avant ma lib�ration, je me fis la promesse sur le vieux cr�ne de construire le plus somptueux des th��tres avant la sortie de prison de mon compagnon de cellule."; break;
        case 874 : texte = "Une fois lib�r�, je partis � la recherche d'un terrain o� construire. Jusqu'au jour o�, poursuivi par des loups, je dus me r�fugier aux bois perdus."; idsuiv=875; break;
        case 875 : texte = "C'est alors que je trouvai cette clairi�re, au fin fond de la for�t, dans un cadre magique, sous l'ombre d'arbres mill�naires..."; break;
        case 876 : texte = "Je commen�ai alors � construire mon op�ra. Les plans furent rapidement pr�ts, mais sans argent pour payer des ouvriers, le travail s'annon�ait long et p�nible."; idsuiv=877; break;
        case 877 : texte = "Alors que je songeais � renoncer, un �trange personnage vint m'apporter le cr�ne, et me rem�morer ma promesse."; break;
        case 878 : texte = "Apr�s des mois de travail, l'op�ra fut achev�. Ce fut le plus bel op�ra jamais vu en Hyrule."; break;
        case 879 : texte = "Tr�s vite, de prestigieux artistes venant de tout le pays vinrent se produire ici. J'avais r�ussi mon r�ve et tenu ma promesse."; break;
        case 880 : texte = "Durant la guerre contre Ganon, des contrebandiers profit�rent du d�sordre pour prosp�rer."; idsuiv=881; break;
        case 881 : texte = "L'un d'entre eux n'�tait autre que mon ancien compagnon de cellule, fra�chement sorti de prison, qui me demanda � se servir de l'op�ra comme planque."; break;
        case 882 : texte = "Une fois la paix revenue, le roi d'Hyrule voulu mettre fin � la contrebande. Il envoya ses meilleurs hommes traquer les responsables."; idsuiv=883; break;
        case 883 : texte = "Pris de panique de peur de tout perdre � cause de ma complicit�, je demandai � mon ancien compagnon de quitter l'op�ra, le mena�ant de le livrer au roi s'il refusait."; break;
        case 884 : texte = "Forc�s de quitter l'op�ra, les bandits m'enferm�rent dans leur ancienne planque ainsi que le personnel, avant d'y mettre le feu."; idsuiv=885; break;
        case 885 : texte = "C'est ainsi que je suis mort, emportant avec moi cet op�ra, qui fut d�truit � jamais..."; break;
        case 886 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>7) {id=893; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=887; chercheText();break;}
            texte = "Tu connais mon histoire, n'as-tu rien � me pr�senter ?"; break;
        case 887 : texte = "J'ai attendu des si�cles ta venue pour r�gler cette vieille dette..."; idsuiv=888; break;
        case 888 : texte = "Faire r�gler la dette ?**              OUI ?            non  "; idsuiv=890; break;
        case 889 : texte = "Faire r�gler la dette ?**              oui              NON ?"; idsuiv=891; break;
        case 890 : texte = "Ma vie fut courte, mais passionnante. Rien de tout cela n'aurait �t� possible sans ton intervention."; buffer="Je tenais � te donner ceci : la scie dont je me suis servi pour construire cet op�ra!"; break;
        case 891 : texte = "...*C'est une blague ?"; break;
        case 892 : texte = "Tu as troqu� la reconnaissance de dette contre une scie."; break;
        case 893 : texte = "Va maintenant, il est temps pour nous de reposer en paix..."; break;
        case 894 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>1) {id=901; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==1 
            && gpJeu->getJoueur()->getObjet()==11) {id=895; chercheText();break;}
            texte = "En tant que barman, je connais toutes les rumeurs...";
            buffer = "En voil� une : ma couleur pr�f�r�e serait le jaune...*Mais je t'ai rien dit, ok ?"; break;
        case 895 : texte = "C'est une jolie pierre jaune que tu as l�... Tu me l'�changes contre ma meilleure bouteille ?"; idsuiv=896; break;
        case 896 : texte = "Cette gemme jaune contre une bouteille, ok ?**              OUI ?            non  "; idsuiv=898; break;
        case 897 : texte = "Cette gemme jaune contre une bouteille, ok ?**              oui              NON ?"; idsuiv=899; break;
        case 898 : texte = "Ouah! Elle est donc � moi!"; break;
        case 899 : texte = "Tsss... personne ne t'en proposera plus pourtant..."; break;
        case 900 : texte = "Tu as troqu� la gemme jaune contre une bouteille de vin."; break;
        case 901 : texte = "Je te sers quelque chose ? Ce sera gratuit pour toi."; break;
        case 902 : 
            if (!gpJeu->getJoueur()->hasObjet(O_OCARINA)) {id=1079; chercheText();break;}
            texte = "Une m�lodie est grav�e sur la st�le :"; break;
        case 903 : texte = "Tu as appris le chant de l'envol ! *Joue-le � l'ext�rieur pour te t�l�porter!"; break;
        case 904 : texte = "Tu as appris le chant du temps invers� ! *Joue-le � l'ext�rieur pour remonter le temps!"; break;
        case 905 : texte = "Tu as appris le chant du temps acc�l�r� ! *Joue-le � l'ext�rieur pour voyager vers le futur!"; break;
        case 906 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>5) {id=913; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==5 
            && gpJeu->getJoueur()->getObjet()==3) {id=907; chercheText();break;}
            texte = "Je suis garde � mi-temps dans cette prison. *En dehors des heures de visite je ne suis pas autoris� � te laisser passer."; break;
        case 907 : texte = "Cette lettre est pour moi ? Elle vient s�rement d'ELLE... Donne-la-moi vite!"; idsuiv=908; break;
        case 908 : texte = "Donner cette lettre ?**              OUI ?            non  "; idsuiv=910; break;
        case 909 : texte = "Donner cette lettre ?**              oui              NON ?"; idsuiv=911; break;
        case 910 : texte = "...*...*..."; buffer="Je dois quitter mon poste... c'est euh... une urgence... T'as l'air d'un bon gars, prends ma place. Ah et garde-moi �a :"; break;
        case 911 : texte = "Ce n'est pas pour moi ?*Tant pis..."; break;
        case 912 : texte = "Tu as troqu� la lettre contre une alliance."; break;
        case 913 : texte = "Je dois y aller!"; break;
        case 914 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>5) {id=921; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==5 
            && gpJeu->getJoueur()->getObjet()==11) {id=915; chercheText();break;}
            texte = "Je suis un brave innocent arriv� ici par erreur... T'aurais pas quelque chose pour m'aider � filer d'ici ?"; break;
        case 915 : texte = "Une... petite cuill�re hein ?"; idsuiv=916; break;
        case 916 : texte = "Donner la cuill�re ?**              OUI ?            non  "; idsuiv=918; break;
        case 917 : texte = "Donner la cuill�re ?**              oui              NON ?"; idsuiv=919; break;
        case 918 : texte = "Merci... ... ...*Tiens, voil� un cadeau de remerciement...*Ca appartenait � mon ancien compagnon de cellule..."; break;
        case 919 : texte = "Je sens qu'une magnifique possibilit� d'�vasion � la petite cuill�re vient de s'envoler..."; break;
        case 920 : texte = "Tu as troqu� la petite cuill�re contre un cr�ne."; break;
        case 921 : texte = "Bon bah... j'ai du boulot hein..."; break;
        case 922 : texte = "Je ne pensais pas que ma mission pouvait �chouer... Les chevaliers hyliens ne sont plus tr�s forts, m�me leur chef commence � faiblir..."; break;
        case 923 : texte = "L'explosion venait de la pi�ce de droite."; break;
        case 924 : texte = "Ainsi voil� celui qui a pu arr�ter le puissant Ganondorf..."; idsuiv=925; break;
        case 925 : texte = "Je suis Agahnim, ancien sage, et mentor de Ganondorf. Quant � toi, tu dois �tre Link..."; idsuiv=926; break;
        case 926 : texte = "Que cela te plaise ou non, nous allons nous emparer de la Triforce.*Adieu !"; break;
        case 927 : texte = "                   Niveau 1 :                                                                                Temple du Courage"; break;
        case 928 : texte = "                   Niveau 2 :                                                                               Temple de la Sagesse"; break;
        case 929 : texte = "                   Niveau 3 :                                                                                Temple de la Force"; break;
        case 930 : texte = "                   Niveau 4 :                                                                                Ruines des Abysses"; break;
        case 931 : texte = "                   Niveau 5 :                                                                                 Pyramide Fant�me"; break;
        case 932 : texte = "                Grande Pyramide"; break;
        case 933 : texte = "               Temple de la Terre"; break;
        case 934 : texte = "                Temple de l'Air"; break;
        case 935 : texte = "                Temple de l'Eau"; break;
        case 936 : texte = "                 Temple du Feu"; break;
        case 937 : texte = "               Temple des D�esses"; break;
        case 938 : 
            if (gpJeu->getAudio()->isSpecial()) {
            texte = "               Ch�teau d'Hyrule"; break;}
            texte = "                 Niveau Final :                                                                               Ch�teau d'Hyrule"; break;
        case 939 : texte = "           Seconde Qu�te - Niveau 1 :                                                                              Casino"; break;
        case 940 : texte = "           Seconde Qu�te - Niveau 2 :                                                                         Tour des Gemmes"; break;
        case 941 : texte = "         Seconde Qu�te - Niveau Final :                                                                      Destination Finale"; break;
        case 942 : texte = "Tu as trouv� la carte !!!**Appuie sur L pour voir le plan du donjon."; break;
        case 943 : texte = "Tu as trouv� la boussole !!!**Les coffres et le boss du donjon sont d�sormais indiqu�s sur la carte."; break;
        case 944 : texte = "Tu as trouv� la cl� du boss !!!**Sers-t'en pour acc�der � son rep�re."; break;
        case 945 : texte = "Tu as trouv� une petite cl�.**Sers-t'en pour d�verrouiller une porte."; break;
        case 946 : texte = "Tu as trouv� un nouveau coeur !!!**Ta vie maximale augmente d'un coeur !!!"; break;
        case 947 : texte = "Tu as trouv� un arc !!!**Equipe-le en appuyant sur Entr�e puis sert-en avec Triangle pour attaquer � distance !"; break;
        case 948 : 
            if (gpJeu->getZone()==47) {id=949; chercheText();break;}
            if (gpJeu->getZone()==48) {id=950; chercheText();break;}
            texte = "Tu as trouv� le M�daillon du Courage !!!"; break;
        case 949 : texte = "Tu as trouv� le M�daillon de la Sagesse !!!"; break;
        case 950 : texte = "Tu as trouv� le M�daillon de la Force !!!"; break;
        case 951 : texte = "Tu as trouv� les Gants de Puissances !!!**Tu peux d�sormais soulever des rochers !"; break;
        case 952 : 
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)) {id=954; chercheText();break;}
            if (gpJeu->getJoueur()->getExplore(1,16,4)) {id=953; chercheText();break;}
            texte = "J'abandonne, t'as gagn�!*Comment as-tu pu d�faire la l�gendaire technique de l'Ultimate LOL ???"; break;
        case 953 : texte = "Tu ne vas pas me laisser m'en sortir comme �a, hein ?*Le code de la salle suivante est 12086... Maintenant va-t-en."; break;
        case 954 : texte = "J'aurais d� rester dans le gang familial..."; break;
        case 955 : texte = "Tu as trouv� la lanterne !!!**Tu peux d�sormais faire jaillir des flammes !"; break;
        case 956 : texte = "Tu as trouv� les palmes !!!**Tu peux d�sormais traverser les �tendues d'eau !"; break;
        case 957 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=960; chercheText();break;}
            texte = "???*Comment as-tu pu arriver jusqu'ici ? *Mon animal de compagnie �tait cens� monter la garde!"; idsuiv=958; break;
        case 958 : texte = "...*Tu dis �tre Link ?*...*Le moment serait-il d�j� venu ?"; idsuiv=959; break;
        case 959 : texte = "Les sbires de Ganon ont fini par d�couvrir mon existence et ont d�truit le village o� je vivais. Je suis alors venu dans ce temple pour me cacher."; idsuiv=960; break;
        case 960 : texte = "Continue ta qu�te Link, nous nous reverrons dans la grotte du portail!"; break;
        case 961 : texte = "Tu as trouv� une meilleure tunique !!!**Ta d�fense augmente d'un point !"; break;
        case 962 : texte = "Tu as trouv� la Cl� du Temps !!!**Va vite la montrer aux sages !"; break;
        case 963 : texte = "Tu as trouv� le Marteau Magique !!!**Tu peux d�sormais aplatir les plots te bloquant le chemin !"; break;
        case 964 : texte = "Tu as trouv� les Gants des Titans !!!**Tu peux d�sormais soulever les pierres les plus lourdes !!!"; break;
        case 965 : texte = "Tu as trouv� une Gemme Jaune !**C'est un tr�sor inestimable !"; break;
        case 966 : texte = "Tu as trouv� l'Arc des F�es !!!**Tes fl�ches ont d�sormais une puissance ph�nom�nale !!!"; break;
        case 967 : texte = "Tu as trouv� une Gemme Verte !**C'est un tr�sor inestimable !"; break;
        case 968 : texte = "Tu as trouv� la Baguette de Glace !!!**Tu peux d�sormais geler les ennemis � distance !!!"; break;
        case 969 : texte = "Tu as trouv� une Gemme Bleue !**C'est un tr�sor inestimable !"; break;
        case 970 : texte = "Tu as trouv� la Baguette de Feu !!!**Tu peux d�sormais lancer de puissantes boules de feu !!!"; break;
        case 971 : texte = "Tu as trouv� une Gemme Rouge !**C'est un tr�sor inestimable !"; break;
        case 972 : texte = "Tu as trouv� un bouclier incroyablement r�sistant !!!*Ta d�fense augmente d'un point !"; break;
        case 973 : texte = "Te voil� enfin."; idsuiv=974; break;
        case 974 : texte = "Croyais-tu vraiment pouvoir prendre de vitesse un mage ma�trisant la t�l�portation ?"; idsuiv=975; break;
        case 975 : texte = "Je dois tout de m�me te remercier. *Trouver ce temple rel�ve de l'exploit. Ganondorf et moi-m�me avons pass� des mois sans trouver un seul cristal."; idsuiv=976; break;
        case 976 : texte = "Et le jour o� enfin, nous en pistions un facilement accessible, tu arrives et terrasses le puissant Ganondorf... *Je dois avouer que je ne m'y attendais pas..."; idsuiv=977; break;
        case 977 : texte = "Toutefois, il semblait �vident que nous poursuivions le m�me objectif, et que tu avais une bonne avance."; idsuiv=978; break;
        case 978 : texte = "Nous avons alors d�cid� de te laisser trouver le temple pour nous."; idsuiv=979; break;
        case 979 : texte = "Tu t'es bien amus� pendant tout ce temps, mais maintenant c'est notre tour."; idsuiv=980; break;
        case 980 : texte = "Je crois qu'il est grand temps pour toi de dispara�tre."; break;
        case 981 : texte = "Comment ??? *Tu n'as pas pu vaincre Agahnim ???"; idsuiv=982; break;
        case 982 : texte = "... *Tout n'est pas perdu, il me reste un espoir..."; break;
        case 983 : texte = "Soit le bienvenu Link. *Nous sommes Din, Nayru et Farore, les D�esses fondatrices d'Hyrule."; idsuiv=984; break;
        case 984 : texte = "Tes efforts pour sauver Hyrule t'ont finalement men� jusqu'� nous."; idsuiv=985; break;
        case 985 : texte = "Comme tu l'as peut-�tre d�j� compris, tu ne peux changer le pass�. Toutes tes actions n'ont eu pour effet que de mettre en place le pr�sent d'o� tu viens."; idsuiv=986; break;
        case 986 : texte = "Ganondorf est venu dans notre temple pour suivre son mentor, et a finalement utilis� la Triforce pour le ramener � la vie."; idsuiv=987; break;
        case 987 : texte = "Il a souhait� obtenir le pouvoir de voyager � sa guise entre le monde des vivants et des morts, mais seuls les d�mons les plus puissants en sont capables."; idsuiv=988; break;
        case 988 : texte = "Gr�ce � ses nouveaux pouvoirs, Ganon a pu ramener Agahnim � la vie, mais sa nouvelle nature a pris le dessus sur sa raison."; idsuiv=989; break;
        case 989 : texte = "Il a transform� Agahnim en zombi � sa solde, s'est proclam� seigneur du malin puis est parti conqu�rir Hyrule."; idsuiv=990; break;
        case 990 : texte = "Le chef du village central a organis� la d�fense d'Hyrule apr�s s'�tre proclam� roi. *Il fit forger Excalibur et fit travailler ensemble chevaliers et sages."; idsuiv=991; break;
        case 991 : texte = "Les chevaliers Hyliens furent d�cim�s, mais leur chef, muni d'Excalibur, repoussa Ganon le temps que les sages le scellent � jamais."; idsuiv=992; break;
        case 992 : texte = "Mais tu connais la suite de l'histoire. Utilisant Agahnim, Ganon �limina les descendants des sages et brisa le seau le retenant prisonnier."; idsuiv=993; break;
        case 993 : texte = "Arm� d'Excalibur, tu repoussas � plusieurs reprises ses assauts, mais le monde des morts ne suffit pas � le retenir."; idsuiv=994; break;
        case 994 : texte = "Ganon a trouv� la Triforce, mais ce n'est pas le seul tr�sor que renferme ce temple..."; idsuiv=995; break;
        case 995 : texte = "La Triforce offrant un pouvoir pratiquement illimit� � son d�tenteur, nous lui avons cr�� un anti Triforce."; idsuiv=996; break;
        case 996 : texte = "Il s'agit de 3 armes d'une puissance exceptionnelle. Si deux d'entre elles s'unissent contre le porteur de la Triforce, elles annuleront son voeu."; idsuiv=997; break;
        case 997 : texte = "L'Ep�e du Courage te revient de droit. Nous te confions �galement l'Arc de la Sagesse pour que tu le donnes � la seule personne qui pourra le manier."; idsuiv=998; break;
        case 998 : texte = "Quant au Trident de la Force, nous l'envoyons au dernier �lu."; break;
        case 999 : texte = "Tu obtiens l'Ep�e du Courage !!! *Cette arme de l�gende d�gage une �norme puissance."; break;
        case 1000: texte = "Tu obtiens l'Arc de la Sagesse !!! *Un pouvoir �trange t'emp�che de l'utiliser..."; break;
        case 1001: texte = "Le temps est venu Link, nous te renvoyons � ton �poque."; break;
        case 1002: texte = "Link! C'est Zelda! Je te parle par t�l�pathie, t'�tais injoignable!"; idsuiv=1003; break;
        case 1003: texte = "Ganon est de retour! Il a attaqu� le ch�teau! *Les gardes ont �t� chang�s en monstres sous son contr�le, soit prudent!"; break;
        case 1004: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1010; chercheText();break;}
            texte = "La salle du tr�ne est plus au Nord."; break;
        case 1005: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getRubisMax()) {id=1013; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1007; chercheText();break;}
            texte = "La Princesse n'est pas encore pr�te � te recevoir."; idsuiv=1006; break; 
        case 1006: texte = "Elle m'a cependant charg� de te dire que des objets � ton intention ont �t� entrepos�s dans la r�serve."; break;
        case 1007: texte = "La Princesse sera bient�t pr�te � te recevoir."; break;
        case 1008:
            if (gpJeu->getJoueur()->getRubisMax()) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<PARLE_GARDE_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_RESERVE) {id=1009; chercheText();break;}
            texte = "Tu as re�u l'autorisation de te rendre � la r�serve ? *Tr�s bien, tu peux passer."; break;
        case 1009: texte = "La r�serve est plus � l'Est"; break;
        case 1010: texte = "Le ch�teau est sous contr�le."; break;
        case 1011: texte = "Tu as trouv� un bouclier !*Ta d�fense augmente d'un point!"; break;
        case 1012: texte = "Tu as obtenu une bourse pouvant contenir 99 Rubis !"; break;
        case 1013: texte = "La Princesse Zelda t'attend."; break;
        case 1014: texte = "Bonjour Link."; break;
        case 1015: texte = "Euh, Link! *Je suis l�!*Ouhou!"; break;
        case 1016: 
            if (gpJeu->getJoueur()->getAvancement()>=PASSAGE_TROUVE) {id=1031; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=ZELDA_SOUS_SOL) {id=1025; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1019; chercheText();break;}
            texte = "Une chose horrible s'est produite cette nuit, Link..."; idsuiv=1017; break;
        case 1017: texte = "L'Ocarina du Temps que tu as ramen� de Termina... *Je le gardais dans une chambre forte du ch�teau, mais il vient d'�tre vol�!"; idsuiv=1018; break;
        case 1018: texte = "J'ai fait placer des gardes dans tout Hyrule, le voleur n'a pas pu aller bien loin..."; idsuiv=1019; break;
        case 1019: texte = "J'aimerai que tu te charges de retrouver l'Ocarina. Commence ton enqu�te par la chambre forte du sous-sol o� il se trouvait, je t'y rejoins."; break;
        case 1020: 
            if (gpJeu->getJoueur()->getAvancement()<PARLE_ZELDA_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_CH_FORTE) {id=1010; chercheText();break;}
            texte = "Les chambres fortes sont par ici."; break;
        case 1021: texte = "L'acc�s � cette chambre forte est strictement interdit."; break;
        case 1022: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_SOUS_SOL) {id=1023; chercheText();break;}
            texte = "La Princesse vous a charg� d'enqu�ter sur le vol de l'Ocarina ? *Dans ce cas vous pouvez entrer, il n'y a de toute fa�on plus rien � garder ici..."; break;
        case 1023: texte = "Je suis rest� � garder cette porte toute la nuit. Je suis certain que personne n'a franchi cette porte..."; break;
        case 1024: texte = "C'est ici qu'�tait gard� l'Ocarina. Le garde a entendu un grand bruit. Le temps qu'il r�alise que cela venait de la chambre forte, le coffre avait �t� vid�."; idsuiv=1025; break;
        case 1025: texte = "Si tu vois quelque chose de louche, mets-toi devant et appuie sur Cercle pour me le signaler."; break;
        case 1026: texte = "C'est une torche... Tu aurais pr�f�r� un lustre au plafond ?"; break;
        case 1027: texte = "Ce coffre contenait l'Ocarina du Temps hier soir encore..."; break;
        case 1028: 
            if (gpJeu->getJoueur()->getAvancement()>=RIDEAUX_REPERES) {id=1030; chercheText();break;}
            texte = "Cette pi�ce donnait sur les �gouts... *Avant de la changer en chambre forte j'ai fait condamner le passage. Les rideaux cachent que cela a �t� mal fait..."; break;
        case 1029: texte = "C'est euh... un canard de bain. *Ne me demande pas ce que cela peut bien faire ici..."; break;
        case 1030: texte = "Ces rideaux ont l'air de t'intriguer... *V�rifions s'il n'y a rien derri�re..."; break;
        case 1031: texte = "Voil� par o� a d� passer le voleur! *Qu'attends-tu ? Pars � sa poursuite!"; break;
        case 1032: texte = "J'ai l'impression qu'on m'a oubli�... *Voil� que je garde une chambre forte vide et grande ouverte..."; break;
        case 1033: texte = "Le voleur doit �tre dans cette for�t, tu ne peux pas abandonner maintenant!"; break;
        case 1034: texte = "TUTORIEL : Appuyez sur Croix pr�s d'un objet l�ger tel qu'un pot pour le soulever. Appuyez une seconde fois pour le lancer."; break;
        case 1035: texte = "TUTORIEL : Appuyez sur Cercle pr�s d'un coffre pour l'ouvrir. Un coffre ne s'ouvre que par le bas."; break;
        case 1036: texte = "                Ch�teau d'Hyrule"; break;
        case 1037: texte = "Ce passage m�ne aux cachots, tu n'as rien � y faire."; break;
        case 1038: texte = "Ce passage m�ne � une zone sous tr�s haute s�curit�. M�me le h�ros d'Hyrule n'est pas autoris� � y p�n�trer."; break;
        case 1039: texte = "Euh... Comment es-tu arriv� l� ?"; break;
        case 1040: texte = "Ces escaliers m�nent aux chambres fortes."; break;
        case 1041: texte = "La salle du tr�ne est derri�re cette porte."; break;
        case 1042: texte = "La salle du tr�ne s'appelle la salle du tr�ne parce qu'elle ne comporte plus qu'un seul tr�ne..."; break;
        case 1043: texte = "La porte de gauche m�ne � la salle de bal et aux quartiers VIP, alors que la porte du haut m�ne � la salle � manger et aux cuisines."; break;
        case 1044: texte = "Autrefois je jouais du piano debout, mais avec les ann�es j'ai d�cid� de me poser."; break;
        case 1045: texte = "Je suis ici comme musicienne, mais les soirs de bal je pr�f�re l�cher la harpe et aller danser."; break;
        case 1046: texte = "J'ai entendu dire qu'un voleur amateur d'instruments de musique est venu au ch�teau durant la nuit."; idsuiv=1047; break;
        case 1047: texte = "Heureusement il n'a pas d� voir mon violon."; break;
        case 1048: texte = "Un petit remontant ?**              OUI ?            non  "; break;
        case 1049: texte = "Un petit remontant ?**              oui              NON ?"; break;
        case 1050: texte = "Cuistot au ch�teau, c'est pas une sin�cure..."; break;
        case 1051: texte = "On dit que les meilleurs cuistots peuvent lire tout en pr�parant leurs plats. Pour ma part j'y arrive � moiti�."; break;
        case 1052: texte = "Je ne sais jamais quoi pr�parer, il faut que je me d�p�che de trouver une id�e!"; break;
        case 1053: texte = "Serveuse au ch�teau, c'est plut�t un bon job, tranquille et bien pay�."; break;
        case 1054: texte = "L'aile Ouest du ch�teau est r�serv�e aux VIPs. Et euh... je n'ai pas eu de consignes � ton sujet... un oubli sans doute."; break;
        case 1055: texte = "L'aile Est du ch�teau est r�serv�e aux gardes. D�sol� mais tu n'as rien � y faire."; break;
        case 1056: texte = "Cette porte m�ne � la r�serve."; break;
        case 1057: texte = "La biblioth�que est un lieu... plut�t calme."; break;
        case 1058: texte = "Tu as obtenu une source d'�nergie!*...*C'est pas si mal..."; break;
        case 1059: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_DONNE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==MOT_DE_PASSE_CONNU) {id=1061; chercheText();break;}
            texte = "L'acc�s � la salle du tr�ne n'est accord� qu'aux personnes autoris�es."; break;
        case 1060: 
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASSE_UTILISE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASS) {id=1063; chercheText();break;}
            texte = "L'acc�s � cette partie du ch�teau n'est accord� qu'au personnel de r�novation."; break;
        case 1061: texte = "Tu connais la phrase secr�te ?*Je me doutais bien que sous tes airs de lapinet tout gentil se cachait un terrible soldat d'�lite de Ganon."; break;
        case 1062: texte = "Tu peux passer."; break;
        case 1063: texte = "Tu as obtenu l'autorisation de t'aventurer dans tout le ch�teau ??? *Et bien passe dans ce cas..."; break;
        case 1064: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_CONNU) {id=1070; chercheText();break;}
            texte = "Tu es venu me lib�rer ? *Je n'avais pas besoin d'aide..."; idsuiv=1065; break;
        case 1065: texte = "Je voulais m'emparer de ce ch�teau par la force... Je suis donc entr� pour d�fier Ganon."; idsuiv=1066; break;
        case 1066: texte = "Le combat fut long et difficile... *Mais les gardes de la salle du tr�ne ont finalement r�ussi � m'arr�ter..."; idsuiv=1067; break;
        case 1067: texte = "Quelle poisse, j'aurai bien voulu rencontrer Ganon..."; idsuiv=1068; break;
        case 1068: texte = "Depuis j'ai entendu dire qu'il y avait une phrase secr�te � donner aux gardes pour passer. Il faut leur dire �a :"; idsuiv=1069; break;
        case 1069: texte = "D�sol�, mais la princesse n'est pas dans ce ch�teau!"; idsuiv=1070; break;
        case 1070: texte = "La prochaine fois j'y arriverai."; break;
        case 1071: texte = "!!!*Mais tu es..."; idsuiv=1072; break;
        case 1072: 
            gpJeu->getAudio()->stopSpecial();
            texte = "Un petit lapin rose ! *J'aime le rose !"; idsuiv=1073; break;
        case 1073: texte = "Fais comme chez toi petit lapin rose, je t'autorise � te promener � ta guise dans ce ch�teau."; break;
        case 1074: 
            if (gpJeu->getJoueur()->isLapin()) {id=1073; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>6) {id=1078; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==6 
            && gpJeu->getJoueur()->getObjet()==15) {id=1075; chercheText();break;}
            texte = "Tu m'es vaguement familier... *Enfin peu importe, tu saurais pas o� je peux trouver une bonne bi�re ?"; break;
        case 1075: texte = "C'est une bi�re que tu as l� ?*Je te la pique, j'imagine que t'es l� pour �a de toute fa�on."; idsuiv=1076; break;
        case 1076: texte = "Tiens, t'as qu'� prendre �a comme r�compense."; break;
        case 1077: texte = "Tu as troqu� la bi�re contre des clous..."; break;
        case 1078: texte = "Je crois que je t'aime bien, t'es un bon gars. *Tu vas me chercher une autre bi�re ?"; break;
        case 1079: texte = "Une partition est grav�e. Si tu avais un instrument de musique tu pourrais essayer de la jouer."; break;
        case 1080: texte = "Tu as... euh... vol� l'ocarina ??? *On va dire que c'est pour la bonne cause..."; break;
        case 1081: texte = "A la seconde o� il joua l'air � l'ocarina, Link fut ramen� � son �poque. Il courut alors au palais pour raconter son histoire � la Princesse..."; break;
        case 1082: texte = "Quelle terrible histoire... *Le Royaume d'Hyrule est-il vraiment destin� � tomber aux mains de Ganon ?"; idsuiv=1083; break;
        case 1083: 
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->hasObjet(O_ARC_OR) < 2) {id=1092; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==4 
            && gpJeu->getJoueur()->getObjet()==11) {id=1085; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->getEnnemi(50)) {id=1112; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5) {id=1095; chercheText();break;}
            texte = "Que pouvons-nous faire ? *Si seulement Ganon n'avait jamais trouv� la Triforce..."; break;
        case 1084: texte = "L'Ocarina transporta Link une fois de plus. Le h�ros d'Hyrule se retrouva alors dans une vaste plaine enneig�e..."; break;
        case 1085: texte = "Ce miroir est pour moi ?**              OUI ?            non  "; idsuiv=1087; break;
        case 1086: texte = "Ce miroir est pour moi ?**              oui              NON ?"; idsuiv=1088; break;
        case 1087: texte = "... Tu m'offres un miroir ??? Tu me prends donc pour ce genre de filles qui passent leur temps � se regarder ???"; 
            buffer = "Bon prends quand m�me �a en remerciement."; break;
        case 1088: texte = "...*Va-t-en vite si tu ne veux pas finir au cachot."; break;
        case 1089: texte = "Tu as troqu� le miroir contre une petite cuill�re !"; break;
        case 1090: texte = "Tu es dans une zone sous haute s�curit�, je vais te demander de partir."; break;
        case 1091: texte = "Tu as trouv� une tunique extr�mement r�sistante!!!*Ta d�fense augmente d'un point !"; break;
        case 1092: texte = "Contente de te voir enfin Link!"; idsuiv=1093; break;
        case 1093: texte = "Tu dis que cet arc est pour moi et qu'il peut vaincre Ganon ?*Cool!"; break;
        case 1094: texte = "Tu as remis l'Arc de la Sagesse � la Princesse Zelda."; break;
        case 1095: texte = "Ne t'en fais pas pour moi, je devrais pouvoir me d�brouiller d�sormais."; idsuiv=1096; break;
        case 1096: texte = "Nous devons affronter Ganon, pars devant je te rejoins.*Je dois me repoudrer le nez avant."; break;
        case 1097: texte = "!!! *Ganon a repris forme humaine! *Ce n'est plus un d�mon il ne pourra plus revenir � la vie, nous avons gagn�!"; break;
        case 1098: texte = "???"; break;
        case 1099: texte = "Te voil� enfin Link. *Cette fois la victoire sera mienne, j'ai am�lior� mes techniques sp�cialement pour te vaincre."; break;
        case 1100: texte = "Nous revoil� face � face Link. *J'ai l'impression de sortir d'un long cauchemar..."; idsuiv=1101; break;
        case 1101: texte = "Agahnim avait tort, la Triforce n'aurait jamais d� �tre trouv�e."; idsuiv=1102; break;
        case 1102: texte = "Ecoute-moi bien Link, il y a d�sormais bien longtemps, Agahnim disparut apr�s avoir quitt� l'ordre de sages."; idsuiv=1103; break;
        case 1103: texte = "Le jour o� il reparut, il �tait dot� de sombres pouvoirs. En tant que sage, il n'aurait jamais �t� capable de lancer des boules de feu, sa sp�cialit� c'�tait les lapins..."; idsuiv=1104; break;
        case 1104: texte = "Je devais trop � Agahnim pour m'opposer � lui, cependant j'ai men� mon enqu�te tandis que nous cherchions les cristaux magiques."; idsuiv=1105; break;
        case 1105: texte = "Il semblerait qu'il ait obtenu ses pouvoirs d'une entit� beaucoup plus dangereuse et puissante que je n'ai jamais pu l'�tre."; idsuiv=1106; break;
        case 1106: texte = "Il reste en Hyrule des lieux que tu n'as pas explor�s et des ennemis que tu n'as pas vaincus. Ta qu�te n'est peut-�tre pas encore finie..."; idsuiv=1107; break;
        case 1107: texte = "Tu veux savoir pourquoi je te dis tout �a ? *J'imagine que je ne vais pas pouvoir m'en sortir si facilement apr�s tout ce que j'ai fait..."; idsuiv=1108; break;
        case 1108: texte = "Si j'�choue aujourd'hui, quelqu'un devra venger Agahnim � ma place. *Mais..."; idsuiv=1109; break;
        case 1109: texte = "... en seras-tu capable ?"; break;
        case 1110: texte = "Tu as trouv� la Triforce !!!"; break;
        case 1111: texte = "C'est ainsi que Ganon fut vaincu � jamais. La Triforce fut une nouvelle fois r�cup�r�e puis gard�e � l'abri au palais. **Cependant, inqui�t� par les derni�res paroles de Ganondorf, Link passa le restant de ses jours � veiller sur Hyrule. ***Fin de la premi�re qu�te."; break;
        case 1112: texte = "Ganon a repris forme humaine... *est-il toujours notre ennemi ?"; break;
        case 1113: texte = "Pr�t pour un dernier duel ?"; break;
        case 1114: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) == 6380) {texte = "Bienvenue au Casino !"; break;}
            texte = "Bienvenue cher visiteur, les droits d'entr�es sont de 10 Ganon d'or, �a te va ?*              OUI ?            non  "; idsuiv=1117; break;
        case 1115: texte = "Bienvenue cher visiteur, les droits d'entr�es sont de 10 Ganon d'or, �a te va ?*              oui              NON ?"; idsuiv=1116; break;
        case 1116: texte = "Tant pis."; break;
        case 1117: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) != 6380 &&
            gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) {id=1118; chercheText();break;}
            texte = "Bienvenue au Casino !"; break;
        case 1118: texte = "Reviens quand tu auras de l'argent l'ami."; break;
        case 1119: texte = "Nous sommes ferm�s pour le moment, reviens plus tard."; break;
        case 1120: texte = "Bienvenue au casino familial, veux-tu que je t'explique les r�gles du jeu pour 5 Ganon d'or?              OUI ?            non  "; idsuiv=1122; break;
        case 1121: texte = "Bienvenue au casino familial, veux-tu que je t'explique les r�gles du jeu pour 5 Ganon d'or?              oui              NON ?"; idsuiv=1116; break;
        case 1122: 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) {id=1118; chercheText();break;}
            texte = "Dans ce casino, les ennemis ne t'enl�vent pas de coeurs mais de l'argent. Chaque attaque te fait perdre un peu plus que la pr�c�dente."; idsuiv=1123; break;
        case 1123: texte = "Si tu n'as plus d'argent, tu es mis � la porte. Les clients fauch�s ne nous int�ressent pas."; idsuiv=1124; break;
        case 1124: texte = "Cependant, en remportant les diff�rents jeux propos�s, tu pourras gagner des prix de grandes valeurs."; break;
        case 1125: 
            if (gpJeu->getJoueur()->getCoffre(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arr�ter sur un signe. Obtient les 4 signes diff�rents et tu gagneras un prix."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1126: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              OUI ?            non  "; break;
        case 1127: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              oui              NON ?"; idsuiv=1116; break;
        case 1128: texte = "Tu as d�j� remport� ce jeu."; break;
        case 1129: texte = "F�licitation !*Voici ton prix :"; break;
        case 1130: texte = "Tu auras sans doute plus de chance la prochaine fois."; break;
        case 1131:
            if (gpJeu->getJoueur()->getCoffre(12,2)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1132; chercheText();break;}
            texte = "Frappe les ennemis pour les arr�ter sur un chiffre. Obtiens un 4, un 2 et un 1 et tu gagneras un prix."; 
            buffer="Parle-moi si tu �choues, tu pourras recommencer en conservant les bons chiffres obtenus."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1132: texte = "Veux-tu compl�ter pour 5 Ganon d'or ?**              OUI ?            non  "; break;
        case 1133: texte = "Veux-tu compl�ter pour 5 Ganon d'or ?**              oui              NON ?"; idsuiv=1116; break;
        case 1134:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->isTempsVisible()) {id=1135; chercheText();break;}
            texte = "C'est la ligne de d�part de la grande course du Casino, tu as 21 secondes pour atteindre l'arriv�e."; 
            idsuiv=1126; break;
        case 1135: texte = "Tu perds du temps l�, tu sais ?"; break;
        case 1136:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            texte = "C'est la ligne d'arriv�e de la grande course du Casino. Va � la ligne de d�part si tu veux essayer de battre le record."; break;
        case 1137:
            if (gpJeu->getJoueur()->getCle(12,0)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arr�ter sur un chiffre et fait plus que moi avec un d� en moins."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1138:
            if (gpJeu->getJoueur()->getCoffre(12,4)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Choisis un chiffre, soit 1, soit 6. Je vais lancer 4 d�s, si ton chiffre y est c'est gagn�, sinon tu paies 10 fois la diff�rence avec le d� le plus proche."; 
            idsuiv=1139; break;
        case 1139: texte = "Veux-tu essayer ?**              OUI ?            non  "; idsuiv=1141; break;
        case 1140: texte = "Veux-tu essayer ?**              oui              NON ?"; idsuiv=1116; break;
        case 1141: texte = "Quel est ton chiffre ?**              UN  ?            six  "; break;
        case 1142: texte = "Quel est ton chiffre ?**              un               SIX ?"; break;
        case 1143:
            if (gpJeu->getJoueur()->getCle(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arr�ter sur un chiffre qui sera transmis � une caisse de droite. Puis pousse les caisses pour qu'elles arrivent � 0 sur les dalles."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1144:
            if (gpJeu->getJoueur()->getCoffre(12,3)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) > 1) {id=1145; chercheText();break;}
            texte = "Je te vends une cl� pour un prix �gal � la somme de tes 4 d�s fois le montant du miens."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1145:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "Je te vends une petite cl� pour "+os.str()+" Ganon d'or, �a te va ?*              OUI ?            non  "; idsuiv=1129; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<tmp) {idsuiv=1118;break;}
            break;
        case 1146:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "Je te vends une petite cl� pour "+os.str()+" Ganon d'or, �a te va ?*              oui              NON ?"; idsuiv=1116; break;
            break;
        case 1147:
            if (gpJeu->getJoueur()->getCle(12,2)) {id=1148; chercheText();break;}
            texte = "La salle du coffre est au bout du couloir � gauche. Seuls les meilleurs clients peuvent esp�rer l'atteindre.";
            break;
        case 1148: 
            if (gpJeu->getJoueur()->getCoeur(11)) {id=1149; chercheText();break;}
            texte = "Tu as ouvert le coffre ?*Tu devrais tenter la salle sp�ciale d�sormais."; break;
        case 1149: texte = "Les gens comme toi n'ont rien � faire dans un casino...*Nous sommes ruin�s..."; break;
        case 1150: texte = "Bienvenue au Grand Quiz du Casino !"; idsuiv=1151; break;
        case 1151: texte = "Ici c'est moi qui pose les questions, et les mauvaises r�ponses co�tent ch�re."; idsuiv=1152; break;
        case 1152: 
            gpJeu->getJoueur()->setCoffre(12,14,0); // ->nb questions pos�es
            for (int i = 0; i < MAX_QUIZZ; i++) gpJeu->getJoueur()->setCoffre(12,15+i,0);
            tmp = rand()%MAX_QUIZZ; idsuiv = 1154 + tmp*4;
            gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            texte = "Je ne te demande pas si tu veux jouer, je suis tout de m�me un boss.*Alors commen�ons..."; 
            break;
        case 1153: 
            if ((MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14)) > 0) {
                tmp = rand()%(MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14));
                for (int i = 0; i <= tmp; i++) {
                    if (gpJeu->getJoueur()->getCoffre(12,15+i) > 0) {
                        tmp++;
                    }
                } 
                idsuiv=1154+tmp*4;
                gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            }
            texte = "Question suivante..."; break;
        case 1154: texte = "Ce Casino contenait un total de 6 jeux diff�rents sans compter ce quiz, est-ce vrai ?              VRAI ?            faux  "; idsuiv=1157; break;
        case 1155: texte = "Ce Casino contenait un total de 6 jeux diff�rents sans compter ce quiz, est-ce vrai ?              vrai              FAUX ?"; idsuiv=1156; break;
        case 1156: texte = "Correct! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des cl�s."; break;
        case 1157: texte = "Non! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des cl�s."; break;
        
        case 1158: texte = "Le gars de la maison du caf� ne boit jamais plus de 16 tasses de caf� par jour, vrai ?*             VRAI ?            faux  "; idsuiv=1161; break;
        case 1159: texte = "Le gars de la maison du caf� ne boit jamais plus de 16 tasses de caf� par jour, vrai ?*             vrai              FAUX ?"; idsuiv=1160; break;
        case 1160: texte = "Correct! Il peut atteindre les 17 tasses!"; break;
        case 1161: texte = "Non! Il peut atteindre les 17 tasses!"; break;
        
        case 1162: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             VRAI ?            faux  "; idsuiv=1165; break;
        case 1163: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             vrai              FAUX ?"; idsuiv=1164; break;
        case 1164: texte = "Correct! Il y en a 200."; break;
        case 1165: texte = "Non! Il y en a 200."; break;
        
        case 1166: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1168; break;
        case 1167: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1169; break;
        case 1168: texte = "Correct! Les 3 autres sont d�truites."; break;
        case 1169: texte = "Non! Il y a 10 maisons dont 3 d�truites, soit plus que 7."; break;

        case 1170: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "Tu es mort "+os.str()+" fois, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1173; break;
        case 1171: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "Tu es mort "+os.str()+" fois, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1172; break;
        case 1172: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "Correct! Tu es mort "+os.str()+" fois."; break;
        case 1173: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "Non! Tu es mort "+os.str()+" fois."; break;
            
        case 1174: texte = "14 mauvaises r�ponses suffisent obligatoirement � faire perdre n'importe quel joueur, vrai ?*             VRAI ?            faux  "; idsuiv=1176; break;
        case 1175: texte = "14 mauvaises r�ponses suffisent obligatoirement � faire perdre n'importe quel joueur, vrai ?*             vrai              FAUX ?"; idsuiv=1177; break;
        case 1176: texte = "Correct! 14 mauvaises r�ponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        case 1177: texte = "Non! 14 mauvaises r�ponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        
        case 1178: texte = "Je suis le boss le plus cool du jeu, vrai ?**             VRAI ?            faux  "; idsuiv=1180; break;
        case 1179: texte = "Je suis le boss le plus cool du jeu, vrai ?**             vrai              FAUX ?"; idsuiv=1181; break;
        case 1180: texte = "H�! H�! On est d'accord."; break;
        case 1181: texte = "... *Je vais te la compter fausse pour le principe..."; break;
        
        case 1182: texte = "Seuls 3 donjons du pass� sont obligatoires pour finir le jeu, vrai ? *             VRAI ?            faux  "; idsuiv=1184; break;
        case 1183: texte = "Seuls 3 donjons du pass� sont obligatoires pour finir le jeu, vrai ? *             vrai              FAUX ?"; idsuiv=1185; break;
        case 1184: texte = "Correct! Le temple de l'air, le temple du feu et celui des d�esses."; break;
        case 1185: texte = "Non! Il n'y en a bien que 3, Le temple de l'air, le temple du feu et celui des D�esses."; break;
        
        case 1186: texte = "Plus de 4000 Ganon d'or sont n�cessaires pour obtenir tous les prix de la grosse f�e, vrai ?              VRAI ?            faux  "; idsuiv=1189; break;
        case 1187: texte = "Plus de 4000 Ganon d'or sont n�cessaires pour obtenir tous les prix de la grosse f�e, vrai ?              vrai              FAUX ?"; idsuiv=1188; break;
        case 1188: texte = "Correct! Il n'en faut que 3798."; break;
        case 1189: texte = "Non! 3798 suffisent."; break;
        
        case 1190: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             VRAI ?            faux  "; idsuiv=1192; break;
        case 1191: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             vrai              FAUX ?"; idsuiv=1193; break;
        case 1192: texte = "Correct! Il y en avait bien 80."; break;
        case 1193: texte = "Non! Il y en avait bien 80."; break;
        
        case 1194: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "Tu as d�j� r�pondu � "+os.str()+" de mes questions, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1197; break;
        case 1195: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "Tu as d�j� r�pondu � "+os.str()+" de mes questions, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1196; break;
        case 1196: texte = "Correct! Mais maintenant oui."; break;
        case 1197: texte = "Non! Mais maintenant oui."; break;
        
        case 1198: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             VRAI ?            faux  "; idsuiv=1200; break;
        case 1199: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             vrai              FAUX ?"; idsuiv=1201; break;
        case 1200: texte = "Correct! Il y en a 16 en tout."; break;
        case 1201: texte = "Non! Il y en a 16 en tout."; break;
        
        case 1202: texte = "Une potion bleue co�te l'�quivalent de 40 Rubis plus 40 Ganon d'or plus 10 pi�ces d'or, vrai ?*             VRAI ?            faux  "; idsuiv=1204; break;
        case 1203: texte = "Une potion bleue co�te l'�quivalent de 40 Rubis plus 40 Ganon d'or plus 10 pi�ces d'or, vrai ?*             vrai              FAUX ?"; idsuiv=1205; break;
        case 1204: texte = "Correct! Soit 160 Rubis."; break;
        case 1205: texte = "Non! Cela donne 160 Rubis, soit le prix d'une potion bleue."; break;
        
        case 1206: texte = "Dans la mine, les rails du wagonnet pouvaient se changer � l'aide de 3 leviers, vrai ?*             VRAI ?            faux  "; idsuiv=1209; break;
        case 1207: texte = "Dans la mine, les rails du wagonnet pouvaient se changer � l'aide de 3 leviers, vrai ?*             vrai              FAUX ?"; idsuiv=1208; break;
        case 1208: texte = "Correct! Il n'y en avait que 2."; break;
        case 1209: texte = "Non! Il n'y en avait que 2."; break;
        
        case 1210: texte = "Il fallait trouver 3 poissons diff�rents pour gagner le concours de p�che, vrai ?*             VRAI ?            faux  "; idsuiv=1213; break;
        case 1211: texte = "Il fallait trouver 3 poissons diff�rents pour gagner le concours de p�che, vrai ?*             vrai              FAUX ?"; idsuiv=1212; break;
        case 1212: texte = "Correct! Il en fallait 5."; break;
        case 1213: texte = "Non! Il en fallait 5."; break;
        
        case 1214: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             VRAI ?            faux  "; idsuiv=1217; break;
        case 1215: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             vrai              FAUX ?"; idsuiv=1216; break;
        case 1216: texte = "Correct! Ton �p�e actuelle en est �galement capable."; break;
        case 1217: texte = "Non! Ton �p�e actuelle en est �galement capable."; break;
        
        case 1218: texte = "Zelda est plus grande que toi, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1221; break;
        case 1219: texte = "Zelda est plus grande que toi, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1220; break;
        case 1220: texte = "Correct! Tu fais un pixel de plus."; break;
        case 1221: texte = "Non! Tu fais un pixel de plus."; break;
        
        case 1222: texte = "Le donjon 3 contient 3 �tages, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1224; break;
        case 1223: texte = "Le donjon 3 contient 3 �tages, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1225; break;
        case 1224: texte = "Correct! Dont un juste pour le boss."; break;
        case 1225: texte = "Non! 2 �tages plus 1 pour le boss, donc 3."; break;
        
        case 1226: texte = "L'incarnation d�moniaque de Link est un lapin rose, vrai ?*             VRAI ?            faux  "; idsuiv=1229; break;
        case 1227: texte = "L'incarnation d�moniaque de Link est un lapin rose, vrai ?*             vrai              FAUX ?"; idsuiv=1228; break;
        case 1228: texte = "Correct! C'est Oni Link."; break;
        case 1229: texte = "Non! C'est Oni Link."; break;
        
        case 1230: texte = "Tingle n'aurait jamais d� exister, vrai ?**             VRAI ?            faux  "; idsuiv=1232; break;
        case 1231: texte = "Tingle n'aurait jamais d� exister, vrai ?**             vrai              FAUX ?"; idsuiv=1233; break;
        case 1232: texte = "Euh... on s'�gare l�, mais je vais te la compter juste."; break;
        case 1233: texte = "... *Pour moi si."; break;
        
        case 1234: texte = "Tu veux me donner des Ganon d'or, vrai ?**             VRAI ?            faux  "; idsuiv=1237; break;
        case 1235: texte = "Tu veux me donner des Ganon d'or, vrai ?**             vrai              FAUX ?"; idsuiv=1236; break;
        case 1236: texte = "Correct! H�las..."; break;
        case 1237: texte = "Merci!"; break;
        
        case 1238: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la d�fense que tu avais, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1241; break;
        case 1239: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la d�fense que tu avais, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1240; break;
        case 1240: texte = "Correct! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        case 1241: texte = "Non! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        
        case 1242: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1244; break;
        case 1243: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1245; break;
        case 1244: texte = "Correct! Ravi de constater que je ne suis pas le seul � avoir compt�!"; break;
        case 1245: texte = "Non! Tu te rends compte que je connais mieux ton domaine que toi ???"; break;
        
        case 1246: texte = "2 � la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1249; break;
        case 1247: texte = "2 � la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1248; break;
        case 1248: texte = "Correct! Enfin je crois."; break;
        case 1249: texte = "Non! Ca doit �tre l'inverse je crois."; break;
        
        case 1250: texte = "Il est possible de finir le jeu en se d�pla�ant uniquement en moonwalk, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1253; break;
        case 1251: texte = "Il est possible de finir le jeu en se d�pla�ant uniquement en moonwalk, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1252; break;
        case 1252: texte = "Correct! Enfin �a ne t'emp�che pas d'essayer."; break;
        case 1253: texte = "Non! Enfin tu peux toujours essayer..."; break;
        
        case 1254: texte = "C'est dans le pass� que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             VRAI ?            faux  "; idsuiv=1257; break;
        case 1255: texte = "C'est dans le pass� que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             vrai              FAUX ?"; idsuiv=1256; break;
        case 1256: texte = "Correct! C'est dans le pr�sent avec les Rubis rouges."; break;
        case 1257: texte = "Non! C'est dans le pr�sent avec les Rubis rouges."; break;
        
        case 1258: texte = "Ton �p�e peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             VRAI ?            faux  "; idsuiv=1261; break;
        case 1259: texte = "Ton �p�e peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             vrai              FAUX ?"; idsuiv=1260; break;
        case 1260: texte = "Correct! Certains ennemis ne craignent pas les coups d'�p�e."; break;
        case 1261: texte = "Non! Certains ennemis ne craignent pas les coups d'�p�e."; break;
        
        case 1262: texte = "L'�nigme du d�sert comptait 6 pierres, vrai ?**             VRAI ?            faux  "; idsuiv=1264; break;
        case 1263: texte = "L'�nigme du d�sert comptait 6 pierres, vrai ?**             vrai              FAUX ?"; idsuiv=1265; break;
        case 1264: texte = "Correct! Par contre je n'ai jamais trouv� l'ordre..."; break;
        case 1265: texte = "Non! T'as sans doute trich� pour la r�soudre..."; break;
        
        case 1266: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "Tu en es � plus de "+os.str()+" heures de jeu, vrai ?**             VRAI ?            faux  "; idsuiv=1268; break;
        case 1267: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "Tu en es � plus de "+os.str()+" heures de jeu, vrai ?**             vrai              FAUX ?"; idsuiv=1269; break;
        case 1268: texte = "Correct! Ca passe vite hein ?"; break;
        case 1269: texte = "Non! Ca passe vite hein ?"; break;
        
        case 1270: texte = "Les poules du pass� sont plus patientes que celles du pr�sent, vrai ?*             VRAI ?            faux  "; idsuiv=1273; break;
        case 1271: texte = "Les poules du pass� sont plus patientes que celles du pr�sent, vrai ?*             vrai              FAUX ?"; idsuiv=1272; break;
        case 1272: texte = "Correct! Je vois que tu es connaisseur."; break;
        case 1273: texte = "Non! T'auras qu'� v�rifier..."; break;
        
        case 1274: texte = "Il �tait possible de p�cher 4 poissons diff�rents au Lac Hylia, vrai ?*             VRAI ?            faux  "; idsuiv=1276; break;
        case 1275: texte = "Il �tait possible de p�cher 4 poissons diff�rents au Lac Hylia, vrai ?*             vrai              FAUX ?"; idsuiv=1277; break;
        case 1276: texte = "Correct! Il y en avait 6 esp�ces diff�rentes."; break;
        case 1277: texte = "Non! Il y en avait 6 esp�ces diff�rentes, il �tait donc possible d'en trouver 4."; break;
        
        case 1278: texte = "Le P�re No�l existe, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1280; break;
        case 1279: texte = "Le P�re No�l existe, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1281; break;
        case 1280: texte = "Correct! Tu l'as d'ailleurs d�j� rencontr�."; break;
        case 1281: texte = "Non! Tu l'as d'ailleurs d�j� rencontr�."; break;
        
        case 1282: texte = "Les montagnes du pass� contenaient 16 pierres, vrai ?*             VRAI ?            faux  "; idsuiv=1285; break;
        case 1283: texte = "Les montagnes du pass� contenaient 16 pierres, vrai ?*             vrai              FAUX ?"; idsuiv=1284; break;
        case 1284: texte = "Correct! Il n'y en avait que 15 bien s�r."; break;
        case 1285: texte = "Non! Il n'y en avait que 15 bien s�r."; break;
        
        case 1286: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             VRAI ?            faux  "; idsuiv=1289; break;
        case 1287: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             vrai              FAUX ?"; idsuiv=1288; break;
        case 1288: texte = "Correct! Il y en a 44."; break;
        case 1289: texte = "Non! Il y en a 44."; break;
        
        case 1290: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets diff�rentes, vrai ?*             VRAI ?            faux  "; idsuiv=1292; break;
        case 1291: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets diff�rentes, vrai ?*             vrai              FAUX ?"; idsuiv=1293; break;
        case 1292: texte = "Correct! Je vois que tu n'as pas oubli� le roc givre."; break;
        case 1293: texte = "Non! Tu as d� oublier le roc givre dans tes comptes."; break;
        
        case 1294: texte = "La tunique verte ne donne qu'un point de d�fense, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1297; break;
        case 1295: texte = "La tunique verte ne donne qu'un point de d�fense, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1296; break;
        case 1296: texte = "Correct! La tunique verte est celle de base et ne donne aucun point de d�fense."; break;
        case 1297: texte = "Non! La tunique verte est celle de base et ne donne aucun point de d�fense."; break;
        
        case 1298: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1300; break;
        case 1299: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1301; break;
        case 1300: texte = "Correct! Le cinqui�me lui vient d'ailleurs de toi."; break;
        case 1301: texte = "Non! Le cinqui�me lui vient d'ailleurs de toi."; break;
        
        case 1302: texte = "La Pyramide du pass� contenait 85 salles, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1305; break;
        case 1303: texte = "La Pyramide du pass� contenait 85 salles, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1304; break;
        case 1304: texte = "Correct! 84 seulement."; break;
        case 1305: texte = "Non! 84 seulement."; break;
        
        case 1306: texte = "Les fl�ches de feu sont plus fortes que celles de glace, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1308; break;
        case 1307: texte = "Les fl�ches de feu sont plus fortes que celles de glace, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1309; break;
        case 1308: texte = "Correct! Les fl�ches de feu ont une force de 10, celles de glace 7."; break;
        case 1309: texte = "Non! Les fl�ches de feu ont une force de 10, celles de glace 7."; break;
        
        case 1310: texte = "Les bombes causent autant de d�g�ts que les coups de marteau, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1313; break;
        case 1311: texte = "Les bombes causent autant de d�g�ts que les coups de marteau, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1312; break;
        case 1312: texte = "Correct! Les bombes ont une force de 5, le marteau 3."; break;
        case 1313: texte = "Non! Les bombes ont une force de 5, le marteau 3."; break;
        
        case 1314: texte = "Quoi ??? Tu m'as vaincu ???**             VRAI ?            vrai  "; break;
        case 1315: texte = "Quoi ??? Tu m'as vaincu ???**             vrai              VRAI ?"; break;
        
        case 1316: texte = "Tu as trouv� le bouclier des D�esses !!!*Ta vie remonte d�sormais en permanence !!!"; break;
        case 1317: texte = "Sur cette pierre est �crite l'histoire d'Hyrule en hylien ancien :"; idsuiv=1318; break;
        case 1318: texte = "Apr�s que les D�esses Din, Nayru et Farore eurent cr�� Hyrule, une entit� mal�fique d'un pouvoir in�gal� arriva pour occuper cette terre."; idsuiv=1319; break;
        case 1319: texte = "Malgr� leurs grands pouvoirs, les D�esses durent admettre qu'elles ne pourraient pas d�truire ce mal."; idsuiv=1320; break;
        case 1320: texte = "...*La suite de l'histoire n'est pas �crite ici. Peut-�tre sur une autre st�le ?"; break;
        
        case 1321: texte = "Tu as trouv� la tunique des D�esses !!!*Ta magie remonte d�sormais en permanence !!!"; break;
        case 1322: texte = "Sur cette pierre est �crite l'histoire d'Hyrule en hylien ancien :"; idsuiv=1323; break;
        case 1323: texte = "Din, Nayru et Farore ne purent se r�soudre � ne rien faire, et d�fi�rent l'entit� d�moniaque."; idsuiv=1324; break;
        case 1324: texte = "Apr�s un long combat perdu d'avance, elles durent accepter un compromis et r�ussirent � disperser le pouvoir de l'entit�."; idsuiv=1325; break;
        case 1325: texte = "Pour ce faire, elles durent cependant cr�er des cr�atures d�moniaques contenant les parcelles du pouvoir de l'entit�."; idsuiv=1326; break;
        case 1326: texte = "Ce qui restait de l'entit� mal�fique fut emprisonn� dans une forme humaine, et ne pourra s'en lib�rer tant que tous les types de monstres n'auront pas �t� vaincus."; break;
        
        case 1327: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              OUI ?            non  "; idsuiv=1329; break;
        case 1328: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              oui              NON ?"; idsuiv=1332; break;
        case 1329: texte = "Les ennemis de ce donjon sont tr�s particuliers, chacune de leurs attaques te fera perdre 2 fois plus de vie que le coup pr�c�dent."; idsuiv=1330; break; 
        case 1330: texte = "Soit donc extr�mement prudent, 7 coups suffiront � t'achever."; idsuiv=1331; break;
        case 1331: texte = "De plus, le nombre d'ennemis que tu as vaincus, ainsi que le nombre de type d'ennemis vaincus sont comptabilis�s. Un certain montant sera n�cessaire pour ouvrir certaines portes."; idsuiv=1332; break;
        case 1332: texte = "Bonne chance Link, quoi qu'il advienne tout finit ici."; break;
        
        case 1333:
            if (gpJeu->getJoueur()->getCoffre(14,9)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 4) {id=1335; chercheText();break;}
            texte = "Elimine au moins 30 ennemis de 4 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1334: texte = "Bonne chance Link."; break;
        case 1335: texte = "Tu as vaincu suffisamment d'ennemis, je t'ouvre..."; break;
        case 1336:
            if (gpJeu->getJoueur()->getCoffre(14,10)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 60 && gpJeu->getJoueur()->getCompteurType() >= 10) {id=1335; chercheText();break;}
            texte = "Elimine au moins 60 ennemis de 10 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1337:
            if (gpJeu->getJoueur()->getCoffre(14,11)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 20 && gpJeu->getJoueur()->getCompteurType() >= 3) {id=1335; chercheText();break;}
            texte = "Elimine au moins 20 ennemis de 3 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1338:
            if (gpJeu->getJoueur()->getCoffre(14,12)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 99 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Elimine au moins 99 ennemis de 12 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1339:
            if (gpJeu->getJoueur()->getCoffre(14,13)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Elimine au moins 30 ennemis de 12 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1340:
            if (gpJeu->getJoueur()->getCoffre(14,14)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 40 && gpJeu->getJoueur()->getCompteurType() >= 6) {id=1335; chercheText();break;}
            texte = "Elimine au moins 40 ennemis de 6 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1341:
            if (gpJeu->getJoueur()->getCoffre(14,15)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 50 && gpJeu->getJoueur()->getCompteurType() >= 7) {id=1335; chercheText();break;}
            texte = "Elimine au moins 50 ennemis de 7 types diff�rents et je t'ouvrirais cette porte."; break;
        case 1342: texte = "Tu as trouv� le masque d'Oni Link !!! *Maintiens R puis L pour te transformer et devenir incroyablement puissant."; break;
        case 1343: texte = "F�licitations Link! Tu as battu chaque type d'ennemi... C'est incroyable..."; idsuiv=1344; break;
        case 1344: texte = "Je te dois �norm�ment, veux-tu �tre pay� maintenant ?"; idsuiv=1345; break;
        case 1345: texte = "Je vais enfin pouvoir reprendre ma vraie forme, pr�pare-toi � prendre cher!*Adieu, H�ros d'Hyrule!"; break;
        case 1346: 
            if (gpJeu->nbEnnemis()==0) {id=1348; chercheText();break;}
            texte = "Vite Link! Utilise l'Ep�e des D�esses pour l'achever d�finitivement!"; break;
        case 1347: 
            if (gpJeu->nbEnnemis()==0) {id=1349; chercheText();break;}
            if (gpJeu->getEnnemi()->getSuivant()->getSpecial(2)<13) {id=1350; chercheText();break;}
            texte = "Pas sur moi andouille..."; break;
        case 1348: texte = "F�licitations Link, rentrons maintenant."; break;
        case 1349: texte = "Justice est faite. Mon ma�tre est enfin veng�."; break;
        case 1350: texte = "Ecarte-toi!"; break;
        case 1351: texte = "Mais qu'est-ce que tu fabriques ?"; break;
        case 1352: texte = "Laisse-moi t'expliquer la raison de notre pr�sence dans le sombre donjon de l'entit� sans nom."; idsuiv=1353; break;
        case 1353: texte = "Apr�s ton d�part du ch�teau qui a suivi ma victoire sur Ganon, Ganondorf m'a remis la Triforce et m'a racont� son histoire."; idsuiv=1354; break;
        case 1354: texte = "Nous sommes rapidement arriv�s � la conclusion que l'homme de l'encyclop�die des monstres �tait hautement louche, alors quand nous avons appris d'un garde que tu �tais all� le voir, nous d�cid�mes de te venir en aide."; idsuiv=1355; break;
        case 1355: texte = "Comme nous le pensions, seule la puissance combin�e des 3 Armes des D�esses mani�es par les 3 Elus pouvait d�truire � jamais ce fl�au."; idsuiv=1356; break;
        case 1356: texte = "Quant � Ganondorf, il n'a plus rien � voir avec le monstre que nous connaissions, il n'y a d�sormais plus de t�n�bres en lui et il est digne de confiance."; idsuiv=1357; break;
        case 1357: texte = "D�sormais Hyrule est en paix, pour de bon. Les monstres ne r�appara�tront plus, le mal est d�finitivement vaincu."; idsuiv=1358; break;
        case 1358: texte = "Alors dis-moi Link, que vas-tu faire de tes vacances ?"; break;
        case 1359: texte = "Hyrule �tait sauv� et toute menace �cart�e. Apr�s de longues aventures, les trois h�ros accomplirent leur destin�e. **Les trois D�esses revinrent en Hyrule les f�liciter, puis repartirent, emportant avec elles la Triforce. **Le puissant Ganondorf devint rapidement chef de la garde et passa le restant de ses jours � prot�ger le pays contre des ennemis qui ne vinrent jamais."; idsuiv=1360; break;
        case 1360: texte = "La princesse Zelda fut c�l�br�e � travers tout le pays et bien plus loin encore comme �tant la souveraine ayant apport� la paix sur le monde. **Quant � Link, pr�f�rant fuir la c�l�brit�, il disparut apr�s cette ultime victoire, et nul ne le revit en Hyrule."; break;
        case 1361: texte = "Apr�s les �v�nements survenus � Termina, la princesse Zelda mit fin � l'exil de Link, annon�ant alors au peuple sa victoire sur son alter �go mal�fique."; idsuiv=1362; break;
        case 1362: texte = "Mais le chevalier hylien, peinant � assumer son statut de h�ros, partit vivre en ermite au fond d'une for�t que lui offrit la princesse."; idsuiv=1363; break;
        case 1363: texte = "L'existence de Termina devant rester secr�te, la princesse tut les �v�nements qui s'y �taient d�roul�s et laissa vivre le peuple ignorant dans une paix illusoire."; idsuiv=1364; break;
        case 1364: texte = "Mais tous deux savaient h�las que, du fond de l'enfer, l'immortel Ganon, tirant son incroyable puissance du voeu"; buffer="originel � la Triforce, rassemblait son arm�e en vue de son prochain assaut."; idsuiv=1365; break;
        case 1365: texte = "Jusqu'au jour o�, apr�s des mois pass�s � guetter une attaque, un �v�nement troublant vint mettre fin � cette interminable attente..."; break;
        case 1366: texte = "HO HE !!! *MESSIRE LINK !!!"; break;
        case 1367: texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
        case 1368: texte = "Reviens me voir quand tu auras une bourse et nous parlerons affaire."; break;
        case 1369: texte = "On a entendu des bruits de bataille, puis plus rien..."; break;
        case 1370: texte = "Que peut-il bien se passer ?"; break;
		case 1371:
            tmp = 0;
            for (int i = 0; i < 9; i++) if (gpJeu->getKeyboard()->getRang(i)) tmp++;
            if (tmp == 9 && gpJeu->getJoueur()->getEnnemi(141)) {id=1372; chercheText();break;}
            texte = "Cette porte m�ne � la salle cach�e. *Obtiens les 9 rangs de la page Records et reviens apr�s avoir obtenu la seconde fin pour y p�n�trer.";
            break;
        case 1372: texte = "Tu peux entrer, H�ros L�gendaire."; break;
        case 1373: texte = "Bienvenue dans la salle cach�e de 3T ! *Et f�licitation pour y �tre arriv� !"; idsuiv=1374; break;
        case 1374: texte = "Moi c'est Vincent, j'ai con�u et cod� ce jeu."; break;
        case 1375: texte = "Coucou, moi c'est Lobal�z. *J'ai aid� � la conception, fait quelques nouveaux graphismes, test� la plupart des donjons, et corrig� les textes."; break;
        case 1376: texte = "Salut, moi c'est Raiden. J'suis le dessinateur de l'�quipe. Je me suis occup� de l'�cran titre et des illustrations (... et aussi des nuages sur les maps m'enfin on s'en fou un peu...)."; idsuiv=1377; break;
        case 1377: texte = "Vous pouvez retrouver mes autres dessins sur http://alandar.deviantart.com"; break;
        case 1378: texte = "Des monstres ont coul� ma barque... *Je suis d�sol�, mais tu vas devoir nager d�sormais...";break;
    }
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Tu as trouv� un quart de coeur !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caract�res possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte � afficher; � chaque d�but de mot, 
    //v�rifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isol�s en d�but de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du d�but du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une �toile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot d�passe
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot � la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    // /
    if(val==47) {src.x=52;src.y=151;}
    
    // @ hylien
    if(val==64) {src.x=4;src.y=151;}
            
    // + hylien
    if(val==43) {src.x=20;src.y=151;}
            
    // = hylien
    if(val==61) {src.x=36;src.y=151;}
            
    //minuscules a-z
    if(val>=97 && val<=122) {src.x=4+16*((val-97)%10); src.y=52+16*((val-97)/10);}
            
    //majuscules A-Z
    if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}   
    // �
    if(val==231) {src.x=148;src.y=34;}
    // �
    if(val==233) {src.x=100;src.y=84;}
    // �
    if(val==234) {src.x=116;src.y=84;}
    // �
    if(val==232) {src.x=132;src.y=84;}
    // �
    if(val==235) {src.x=132;src.y=151;}
    // �
    if(val==224) {src.x=148;src.y=84;}
    // �
    if(val==226) {src.x=148;src.y=103;}
    // �
    if(val==228) {src.x=148;src.y=135;}
    // �
    if(val==238) {src.x=84;src.y=119;}
    // �
    if(val==239) {src.x=116;src.y=151;}
    // �
    if(val==251) {src.x=84;src.y=103;}
    // �
    if(val==249) {src.x=148;src.y=151;}
    // �
    if(val==252) {src.x=116;src.y=135;}
    // �
    if(val==246) {src.x=132;src.y=135;}
    // �
    if(val==244) {src.x=148;src.y=119;}
            
    //ponctuation
    // -
    if(val==45) {src.x=102;src.y=34;}
    // .
    if(val==46) {src.x=118;src.y=34;}
    // ,
    if(val==44) {src.x=134;src.y=34;}
    // !
    if(val==33) {src.x=3;src.y=135;}
    // ?
    if(val==63) {src.x=19;src.y=135;}
    // (
    if(val==40) {src.x=35;src.y=135;}
    // )
    if(val==41) {src.x=51;src.y=135;}            
    // ' ( avec @ )
    if(val==39) {src.x=67;src.y=135;}
    // :
    if(val==58) {src.x=83;src.y=135;}
    // ... ( avec % )
    if(val==37) {src.x=101;src.y=135;}
    // >
    if(val==62) {src.x=100;src.y=151;}
    // <
    if(val==60) {src.x=84;src.y=151;}
            
    //chiffres            
    if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
