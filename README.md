# MakefileMaker
-------------

![Release](https://img.shields.io/badge/Release-v1.0-brightgreen?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![Librarie](https://img.shields.io/badge/Librarie-Gtk-green?style=for-the-badge)
![Size](https://img.shields.io/github/repo-size/ARKAGEDON/MakefileMaker?label=SIZE&style=for-the-badge)
![Licence](https://img.shields.io/github/license/ARKAGEDON/MakefileMaker?style=for-the-badge)
![OpenSource](https://img.shields.io/badge/OpenSource-blue?style=for-the-badge&logo=opencollective&logoColor=white)

## Makefile Maker qu'est ce que c'est ?  
Il s'agit d'un générateur de Makefile basique pour un projet composé d'un fichier main, un fichier fonction et un fichier de librairie (ou autre fichier de fonction)  
MakefileMaker permet de simplifier la tâche pénible de créer son makefile et/ou de l'adapter pour le projet actuel  

## Comment ça marche ?  
MakefileMaker se veut être un logiciel simple d'utilisation, en arrivant sur l'application vous avez le choix entre 2 types de makefile:  
- ![Image Makefile simple](https://i.imgur.com/G58rirc.png)  
Les makefiles simples, tout les règles de compilation sont décrites explicitement, aucune variable n'est utilisé ni rien.  
Pour l'utiliser il suffit de remplir les différents champs, le premier est le choix de votre compilateur (GCC par défaut), puis le nom de votre fichier de fonction (__Attention à ne pas mettre l'extension du fichier, juste son nom suffit__), puis le nom de votre fichier de librairie (__Attention à ne pas mettre l'extension du fichier, juste son nom suffit__), et enfin vos flags de compilation (__Ne pas oublier les - devant vos flags, par exemple: -Wall__).  

- ![Image Makefile avancé](https://i.imgur.com/zqbfSHg.png)  
Les makefiles avancés, le makefile est optimisé pour avoir le moins de contenu possible, les variables sont utilisés et les règles de compilation sont implicites.  
Pour l'utiliser il suffit de remplir les différents champs, le premier est le choix de votre compilateur (GCC par défaut), puis le nom de votre fichier de fonction (__Attention à ne pas mettre l'extension du fichier, juste son nom suffit__), puis le nom de votre fichier de librairie (__Attention à ne pas mettre l'extension du fichier, juste son nom suffit__), puis l'emplacement de votre dossier source (__Pour être sur que ce dossier soit sélectionner cliquer sûr un des fichiers que le dossier source contient__), puis l'emplacement du dossier object si vous en souhaitez un (__Pareil suffit de cliquer sur un fichier dans ce dossier pour être sûr qu'il soit sélectionné__) et enfin vos flags de compilation (__Ne pas oublier les - devant vos flags, par exemple: -Wall__).  

## Compilation & installation:  

Pour installer le projet il suffit d'executer les commandes suivantes et d'avoir GTK 3.0 d'installer sur votre machine:  

    git clone https://github.com/ARKAGEDON/MakefileMaker.git
    cd MakefileMaker && make

Pour gtk:  
__Arch & dérivés__:
    
    sudo pacman -S gtk3
__Ubuntu & Debian:__
    
    sudo apt-get install libgtk-3-0

## Contribution au projet:  
  
Tout le monde est libre de contribuer au projet pour corriger les eventuels fautes de Français, code ou dans les makefiles, etc..
Pour cela il suffit de faire un pull request :)

## License:  
Ce projet est sous la license GNU GPL v3.0, aller voir `LICENSE.md` pour plus d'informations.

