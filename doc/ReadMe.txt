1.	Beskrivning

Det som har skapats är en kopia av flappy bird spelet. Det är en fågel som spelaren kontrollerar med avsikt om att navigera genom en scen mellan olika rör (eng. Pipes) med målet om att få en så hög score som möjligt. Det som inkluderas i spelet är levels där vid vart 10 score så ökas svårigheten, tangentbordskomandon, ljudeffekter, etc. 

2.	Instruktion för att bygga och testa

Spelet behöver följande includes:
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h> 
#include <SDL2/SDL_mixer.h>

Se till att updatera include path och library path i make filen då dem är specifika till en local dator. Sedan beroende på vilket system som testar spelet, avkommentera och kommentera bort de lämpliga linker flags och kompilator.

När makefilen har anpassats till testarens lokala dator som har de nödvändiga libraries och includes, så kommer spelet att vara körbart genom att öppna projektet i en “Integrated terminal” och under projektet köra kommandot “make” och sedan “./build/debug/play” 

När spelet väl är körbart kommer en animerad fågel som svävar att visas, som spelare kan du då använda följande kontroller:

Space/vänsterklick - Får fågeln att hoppa/flaxa upp
R – Börjar om spelet
P- pausar spelet (tryck P igen för att fortsätta eller space/vänsterklick för att fortsätta med ett hopp)
M – tystar spelet
Pil up – ökar volym
Pil ner – minskar volym
Esc – stänger ner programmet

När det kommer till resursfiler så är det viktigt att filerna är så som dem är i zip-filen, särskilt resursfilerna som måste vara organiserade så här, notera att den ligger precis under projektkatalog:
•	Flappy-Bird-Game\resources\fonts
    o	\PressStart2P.ttf

•	Flappy-Bird-Game\resources\images
    o	\bird-wing-down.png
    o	\bird-wing-midway.png
    o	\bird-wing-up.png
    o	\flappy-bird-background.jpg
    o	\pipe.png

•	Flappy-Bird-Game\resources\sounds
    o	\flap.wav
    o	\hit.wav
    o	\level-up.wav

Gameplay
• start the game by pressing space or mousclick
• the bird will make a flap and then begin to fall, as the player you need to controll the bird by flapping to navigate through the pipes.
• avoid the pipes, the scene floor and the roof, as you go through the pipes your score increases
• everytime the score increases by 10, the difficulty increases by increasing the birds speed by 20%, as you progress the game get's harder and harder.
• when you die, you get a gameover screen that show your score and what your highscore is. You can also chose to restart the game by pressing restart.


