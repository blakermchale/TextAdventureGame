#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

bool GameState = true; //Game state is on if true
int progress = 0;   //Checks progress of game
string Zone;    //Variable for the current zone
vector<string> Inventory;   //List of spots in inventory
string Equipped[6]; //Lists of spots for equipped items
string BattleState = "No";  //Variable for if the battle will occur
string escaped = "No";  //Variable for if you escaped
int Monster [3][2] =    //List of attributes of monster. From left to right: Serpent, Bear
        {
                {40, 30},   //Health of monster
                {6 ,  8},   //attack high of monster
                {1 ,  2}    //attack low of monster
        };
int MonsterAttack;
int UserMaxHealth = 20;    //User Max Health
int UserHealth = 20;   //Current User Health
bool battleMove, found;        //Keeps track of if an action is made by the player

int Attack()   //Function for attacking
{
    int UserAttack; //Creates variable for user attack
    int CriticalChance = rand()%100 + 1;    //Gives a random number at the start of each attack

    if (Equipped[0] == "dagger")    //When using the dagger do this
    {
        if (Zone == "Sea")
        {
            UserAttack = rand()%(5 - 2) + 1;    //Picks random damage value from 4-8
            Monster[0][0] -= UserAttack;    //Damage monstsers health
            if (CriticalChance >= 80)   //20% chance that a critical hit will occur
            {
                Monster[0][0] -= UserAttack;    //Attacks second time
                cout << "Critical hit!! The blade swiftly cuts the serpents chest, causing the serpent to writhe in pain." << endl;
            }
            else if (UserAttack >= 3)   //Dialogue for a high attack
            {
                cout << "Your swing of the dagger pierces deeply into the skin of the serpent." << endl;
            }
            else    //Dialogue for low attack
            {
                cout << "Tiny swords are not meant to defeat mighty giants. You leave a small cut on the serpent." << endl;
            }

        }
        else if (Zone == "Cavern")
        {
            UserAttack = rand() % (5-2) + 1;    //Picks random damage value from 4-8
            Monster[0][1] -= UserAttack;    //Damage monstsers health
            if (CriticalChance >= 80)   //20% chance that a critical hit will occur
            {
                Monster[0][1] -= UserAttack;    //Attacks second time
                cout << "Critical hit!! You swing your dagger in one fluid motion cutting the bear across its chest multiple times."
                        << endl;
            } else if (UserAttack >= 3)   //Dialogue for a high attack
            {
                cout << "A precisely aimed attack from the dagger strikes the bears knees leaving it immobilized." << endl;
            } else    //Dialogue for low attack
            {
                cout << "Your puny dagger, barely cuts the bear."
                     << endl;
            }
        }
    }
    else if (Equipped[0] == "great broad sword")
    {
        if (Zone == "Sea")
        {
            UserAttack = rand() % 6 +1;    //Picks random damage value from 4-8
            Monster[0][0] -= UserAttack;    //Damage monstsers health
            if (CriticalChance >= 80)   //20% chance that a critical hit will occur
            {
                Monster[0][0] -= UserAttack;    //Attacks second time
                cout
                        << "Critical hit!! Your great broad sword sweeps across the serpents body leaving deep ravished wounds."
                        << endl;
            } else if (UserAttack >= 3)   //Dialogue for a high attack
            {
                cout << "The serpent squirms as you hit its neck, dealing lots of damage." << endl;
            } else    //Dialogue for low attack
            {
                cout << "You lunge at the serpent but its thick hide blocks most of your attack." << endl;
            }
        }
        else if (Zone == "Cavern")
        {
            UserAttack = rand() % 6 + 1;    //Picks random damage value from 4-8
            Monster[0][1] -= UserAttack;    //Damage monsters health
            if (CriticalChance >= 80)   //20% chance that a critical hit will occur
            {
                Monster[0][1] -= UserAttack;    //Attacks second time
                cout
                        << "Critical hit!! The blade buries itself into the bear's shoulder, leaving it disoriented and in severe pain."
                        << endl;
            } else if (UserAttack >= 3)   //Dialogue for a high attack
            {
                cout << "The hilt of your blade bashes the bear across the head, leaving you room to deal a lot of damage." << endl;
            } else    //Dialogue for low attack
            {
                cout << "Your great broad sword lifts into the air, going for a powerful strike. However, the bear dodges at the last second and you gently graze it." << endl;
            }
        }
    }

}

int Defend()   //Function for defending
{
    int Heal;
    if (Equipped[1] == "kite shield")//Checks to see what shield is equipped
    {
        cout << "Your Shield lifts into the air blocking a strike from the monster and giving you time to heal." << endl;
        Heal = rand()%6 + 1;   //Heals user randomly from 1-6 HP
        MonsterAttack -= 2;  //Monsters attack is decreased by 4
        UserHealth += Heal; //Heals the player for certain amount
        if (UserHealth >= UserMaxHealth) //Makes it so user cannot heal more than max health
        {
            UserHealth = UserMaxHealth;
        }
        if (MonsterAttack < 0)
        {
            MonsterAttack = 0;
        }
    }
}
void checkBag (string choice)   //Function for finding items in the inventory
{
    found = false;  //Makes item find false initially
    for (int spot = 0; spot < Inventory.size(); spot++) //When the players choice for an item is found set statement to true
    {
        if(choice == Inventory[spot])
        {
            found = true;
            break;
        }
    }
}
int Item()          //Function for item use
{
    string BagState = "Open";   //Variable for bag condition
    string Choice;  //variable for the item the user wants to use
    cout << "You look into the bag and find these items:\n\n";
    for (int spot = 0; spot < Inventory.size(); spot++)   //Outputs all items in inventory
    {
        cout << "      " << Inventory[spot];
        if (spot%5 == 0 && spot > 0)    //Spaces out the items in rows for every 5
        {
            cout << endl;
        }
    }
    cout << "\n\n";
    if (BattleState == "Yes" || BattleState == "yes")
    {
        cout << "What item would you like to use? Or would you like to exit?(Exit/[Item name])\n\n";
    }
    else
    {
        cout << "What weapon or shield would you like to equip? Or would you like to use an item? ([Item Name]/Exit)\n";
    }
    cin.ignore();
    while (BagState == "Open")  //When bag is open do this
    {
        getline(cin, Choice, '\n'); //Gets user input for choice
        checkBag(Choice);
        if (Choice == "healing potion" && found == true) //User uses healing potion
        {
            cout << "The warm drink passes down your throat refreshing you and healing you for 15 HP." << endl;
            UserHealth += 15;
            if (UserHealth >= UserMaxHealth) //Makes it so user cannot heal more than max health
            {
                UserHealth = UserMaxHealth;
            }
            for (int spot = Inventory.size() - 1; spot >= 0; spot--)   //Checks inventory
            {
                if (Inventory[spot] == "healing potion")    //Gets rid of healing potion after use
                {
                    Inventory.erase(Inventory.begin() + spot);
                    break;
                }
            }
            BagState = "Closed";
        }
        else if (Choice == "spike bomb" && found == true && (BattleState == "Yes" || BattleState == "yes"))
        {
            cout << "You chuck the spike bomb at the creature and inflict 10 damage." << endl;
            if (Zone == "Sea")
            {
                Monster[0][0] -= 10;    //Deals damage to serpent
            }
            else if (Zone == "Cavern")
            {
                Monster[0][1] -= 10;    //Deals damage to bear
            }
            for (int spot = Inventory.size() - 1; spot >= 0; spot--)   //Checks inventory
            {
                if (Inventory[spot] == "spike bomb")    //Gets rid of healing potion after use
                {
                    Inventory.erase(Inventory.begin() + spot);
                    break;
                }
            }
            BagState = "Closed";
        }
        else if (Choice == "dagger" && found == true && (BattleState == "No" || BattleState == "no"))
        {
            Equipped[0] = "dagger"; //Equips dagger
            cout << "\n The dagger is now equipped as your primary weapon.\n";
            BagState = "Closed";
        }
        else if (Choice == "kite shield" && found == true && (BattleState == "No" || BattleState == "no"))
        {
            Equipped[1] = "kite shield";    //Equips shield
            cout << "\n The kite shield is now equipped as your shield.\n";
            BagState = "Closed";
        }
        else if (Choice == "great broad sword" && found == true && (BattleState == "No" || BattleState == "no"))
        {
            Equipped[0] = "great broad sword";  //Equips great broad sword
            cout << "\n The great broad sword is now equipped as your primary weapon.\n";
            BagState = "Closed";
        }
        else if (Choice == "exit" || Choice == "Exit")
        {
            BagState = "Closed";    //Closes bag
            battleMove = false; //Tells user that no move has occurred
        }
        else    //Function for improper item use
        {
            cout << "That cannot be used. Choose again.([Item Name]/Exit)" << endl;
        }
    }
}
void escape()               //Function for escaping battle
{
    escaped = "No"; //Sets user to not escaped yet
    int escapeChance = rand()%100 + 1;  //random escape chance
    if (escapeChance <= 70) //30% chance of escaping
    {
        escaped = "Yes";
        cout << "You dart away from the monster with a sliver of your soul remaining." << endl;
    }
}

void BattleMenu (int MonsterHighAttack, int MonsterLowAttack)
{
    string Action;  //String for the action performed
    MonsterAttack = rand()%(MonsterHighAttack + 1 - MonsterLowAttack) + MonsterLowAttack;   //Sets Monster attack randomly
    cout << "What do you do?(Attack, Defend, Item, Escape)" << endl;
    cin >> Action;  //User input for battle choice

    if (Action == "Attack" || Action == "attack")      //If user inputs attack
    {
        Attack();   //Calls attack function
    }
    else if (Action == "Defend" || Action == "defend")  //If user defends
    {
        Defend();   //Call defend function
    }
    else if (Action == "Item" || Action == "item")
    {
        Item(); //Call Item function
    }
    else if (Action == "Escape" || Action == "escape")
    {
        escape();   //Call escape function
        if (escaped == "Yes")   //When battle has been escaped exit battle
        {
            BattleState = "No";
            battleMove = false; //Makes it so monster will not perform next turn
        }
    }
    else
    {
        cout << "You stand there frozen with fright.."; //Dialogue for improper command
        battleMove = false;     //Tells that no correct action has been selected
    }
    if (battleMove == true)
    {
        UserHealth -= MonsterAttack;    //User takes damage
        if (MonsterHighAttack == Monster[1][0])
        {
            if (MonsterAttack >= 4)  //Indicates high monster attack
            {
                cout << "The serpent strikes you with its 12 inch fangs and leaves a deep wound.\n";
            }
            else if (MonsterAttack < 4)  //Indicates low monster attack
            {
                cout << "The serpent whips its tail at you, but you only stagger a little bit.\n";
            }
            else if (MonsterAttack == 0)    //When monster attack is zero state this
            {
                cout << "The serpent staggers back in awe.\n";
            }

        }
        else if (MonsterHighAttack == Monster [1][1])
        {
            if (MonsterAttack >= 6)   //When monsters damage is high
            {
                cout << "The bears claws rip at your clothing, leaving a gash along your abdomen.\n";
            }
            else if (MonsterAttack < 6) //When monsters damage is low
            {
                cout << "The bears arm sweeps you off your feet, but does not deal much damage.\n";
            }
            else if (MonsterAttack == 0)    //When monster deals no damage
            {
                cout << "The bear goes for your head, but misses and falls on its back.\n";
            }
        }
        cout << endl;
        cout << "Your health is currently: " << UserHealth << " HP" << endl;
        cout << endl;
    }
}

void Battle()
{
    if (Zone == "Sea")  //Different battle dialogue for sea zone
    {


        while(BattleState == "Yes" || BattleState == "yes") //Makes sure battle is still on
        {
            battleMove = true;
            if (Monster[0][0] <= 0)    //If the monster dies use this dialogue, exit battle
            {
                cout << "You climb up the serpent, weaving through its spiny back, and finally reach the top." << endl;
                cout << "In that moment you drill your weapon into the monsters eye and watch as the monster crumbles to the ground." << endl;
                cout << "The battle has exhausted you and you walk back to shore." << endl;
                BattleState = "No"; //Batlle exits
                progress++; //Add level to progress
                break;
            }
            else if (UserHealth <= 0)   //If user dies end game
            {
                cout << "The serpent raises its head high above you and comes crashing down. The world turns to darkness. You die." << endl;
                BattleState = "No"; //Battle exits
                GameState = false;  //Game is ended
                break;
            }
            else if (Monster[0][0] <= 8)   //When monster health is less than 20% tell the user it is close to death
            {
                cout << "The serpent is becoming slower and weaker. It must be close to death." << endl;
                cout << endl;
            }
            BattleMenu(Monster[1][0], Monster[2][0]);
        }


    }
    else if (Zone == "Cavern")  //Different battle dialogue for sea zone
    {


        while(BattleState == "Yes" || BattleState == "yes") //Makes sure battle is still on
        {
            battleMove = true;
            if (Monster[0][1] <= 0)    //If the monster dies use this dialogue, exit battle
            {
                cout << "Your " << Equipped[0] << " falls to the ground and the bear lunges at you with its jaws.\n";
                cout << "Your life flashes before your eyes, as you remember that you have a " << Equipped[1] <<  ".\n";
                cout << "You lift it into the air and bash the bears skull. The bear falls motionless onto the ground." << endl;
                cout << "You leave the bear's den.\n";
                BattleState = "No"; //Batlle exits
                progress++; //Add level to progress
                break;
            }
            else if (UserHealth <= 0)   //If user dies end game
            {
                cout << "You stumble back and trip over a rock. The bears seizes this opportunity and thrashes at you with its claws. You die." << endl;
                BattleState = "No"; //Battle exits
                GameState = false;  //Game is ended
                break;
            }
            else if (Monster[0][1] <= 6)   //When monster health is less than 20% tell the user it is close to death
            {
                cout << "The bear stumbles back losing its footing. It seems exhausted" << endl;
                cout << endl;
            }
            BattleMenu(Monster[1][1], Monster[2][1]);   //Calls battle menu with specific monster attack range
        }


    }
}


void Direction(string direction)
{
    string MoveState = "No";
    string equipChoice; //choice for equipping weapon or shield
    if (direction == "Inventory" || direction == "inventory")   //Checks if user input inventory
    {
        Item();

        cout << "\nYou look back up." << endl;

    }
    else if (direction == "Quit" || direction == "quit")
    {
        GameState = false;
    }
        /*Dialogue for directions and movement in the Barren Field Zone*/
    else if (Zone == "Barren field")
    {
        if (direction == "Right" || direction == "right")
        {
            cout << "You hear a loud screech that sends shivers down your spine. An ominous cloud rolls through the sky, as you look onto the horizon where a mountain lays." << endl;
            cout << "Do you head towards the mountain?(Yes or No)" << endl;
            cin >> MoveState;
            if (MoveState == "Yes" || MoveState == "yes") //Moves user toward mountain
            {
                Zone = "Mountain";
                cout << "The trek towards the mountain is long and treacherous. After many hours and days you reach the mountain." << endl;
            }
            else if (MoveState == "No" || MoveState == "no") //keeps user in place
            {
                cout << "You stay put." << endl;
            }
        }
        else if (direction == "Left" || direction == "left")
        {
            cout << "A cold breeze hits your  face as you see a dark ocean some ways down the field." << endl;
            cout << "You see flashes of light as bolts of lightning strike the sea." << endl;
            cout << "Do you head towards the sea?(Yes/No)" << endl;
            cin >> MoveState;
            if (MoveState == "Yes" || MoveState == "yes") //Moves user towards sea
            {
                Zone = "Sea";
                cout << "You walk towards the water, in hope that you can find something." << endl;
            }
            else if (MoveState == "No" || MoveState == "no")//Keeps user in the field
            {
                cout << "You stay put." << endl;
            }
        }
        else if (direction == "Forward" || direction == "forward")
        {
            cout << "A dense gloomy forest borders the field. It seems to be impossible and dangerous to walk through without a light source of some sort." << endl;
            cout << "Do you head towards the forest?(Yes/No)" << endl;
            cin >> MoveState;
            if (MoveState == "Yes" || MoveState == "yes")//Moves the user towards the forest
            {
                cout << "As you approach the dense woodland you hear a howl. It does not frighten you and you continue pushing into the trees. A second howl is heard and then a third. The darkness scares you and you try to turn back. However, just as you turn a musty dire wolf steps in front of you. You have no time to react and become the wolf's next meal. You die." << endl;
                GameState = false;
            }
            else if (MoveState == "No" || MoveState == "no")//Keeps user in place
            {
                cout << "You stay put." << endl;
            }
        }
        else if (direction == "Backward" || direction == "backward")
        {
            cout << "You stare into the distance. Barren fields cover the lands for miles. There is no place for you to go in that direction." << endl;
        }
        else
        {
            cout << "You look confused...";
        }


    }
        /*Dialogue for directions and movement in the Sea Zone*/
    else if (Zone == "Sea")
    {
        if (direction == "Right" || direction == "right")
        {
            cout << "To your right is a pile of bones that goes towards the sky. One wonders who put them there...\n";
            checkBag("great broad sword");
            if (found == false)
            {
                cout << "Is that something in the bones? You scower through the pile and find a great broad sword.\n It seems that its previous owner has left it behind...\n";
                Inventory.insert(Inventory.end(), "great broad sword");  //Stores Item
            }
        }
        else if (direction == "Left" || direction == "left")
        {
            cout << "The beach goes on for miles and miles. There is no end to the sand. There is nothing over there for you." << endl;
        }
        else if (direction == "Forward" || direction == "forward")
        {
            if (Monster[0][0] > 0)
            {
                cout << "You look ahead and see movement in the ocean. CRASH! A green scaly serpent erupts fron the sea towering over you." << endl;
                cout << "It opens its jaws and lets out a loud roar." << endl;
                cout << "Do you battle the serpent?(Yes/No)" << endl;
                cin >> BattleState;     //Checks what the user wants to do
                if (BattleState == "Yes" || BattleState == "yes")   //Initiates battle
                {
                    cout << "You approach the serpent in the sea with weapon held high. The serpent flares its nostrils as you start the battle." << endl;
                    Battle();
                }
                else if (BattleState == "No" || BattleState == "no")    //Keeps the user away from the monster
                {
                    cout << "The serpent menacingly stares at you as you look away." << endl;
                }
            }
            else
            {
                cout << "You see the serpent lying in the sea. Waves crash and tear at the lifeless body. There is nothing left for you here." << endl;
            }
        }
        else if (direction == "Backward" || direction == "backward")
        {
            cout << "You look out into the barren field from which you came." << endl;
            cout << "Would you like to head towards the field?(Yes/No)" << endl;
            cin >> MoveState;   //User input for movement
            if (MoveState == "Yes" || MoveState == "yes")   //Takes user back to Barren Field zone
            {
                Zone = "Barren field";  //Sets zone to field
            }
            else if (MoveState == "No" || MoveState == "no")
            {
                cout << "You stay put." << endl;
            }
        }
        else
        {
            cout << "You look confused...";
        }

    }
        /*Dialogue for directions and movement in the Mountain Zone*/
    else if (Zone == "Mountain")
    {
        if (direction == "Right" || direction == "right")
        {
            cout << "Ahead of you is an eery cavern, that does not seem to have been touched for centuries.\n";
            cout << "Do you head inside?(Yes/No)\n";
            cin >> MoveState;
            if (MoveState == "Yes" || MoveState == "yes")
            {
                Zone = "Cavern";    //Sets zone to cavern
                cout << "You delve into the cave and begin exploring.\n";
            }
            else if (MoveState == "No" || MoveState == "no")
            {
                cout << "You stay put." << endl;
            }
        }
        else if (direction == "Left" || direction == "left")
        {
            cout << "A sharp cliff lays before you and it cannot be scaled." << endl;
        }
        else if (direction == "Forward" || direction == "forward")
        {
            cout << "Towering above you is the jagged cliff side of the mountain. As you examine the cliff, you hear the screech again and see a burst of fire come from behind the peak of the mountain. It is not wise to climb without the proper tools." << endl;
            cout << "Do you attempt the climb?(Yes/No)" << endl;
            cin >> MoveState;   //Asks user if they want to climb
            if (MoveState == "Yes" || MoveState == "yes")
            {
                cout << "You go over to the cliff and begin climbing. Before you know it you are 50 feet in the air. As you attempt at reaching your next foothold, the rock you were grasping falls away. All contact with the cliff is lost and you end up plummeting to your death." << endl;
                GameState = false;  //Ends game
            }
            else if (MoveState == "No" || MoveState == "no")
            {
                cout << "You stay put." << endl;
            }
        }
        else if (direction == "Backward" || direction == "backward")
        {
            cout << "A vast field stretches out before you. Dead grass stretches for miles. Its the field from which you started this journey." << endl;
            cout << "Would you like to head towards the field?(Yes/No)" << endl;
            cin >> MoveState;   //Asks user if they want to move to the field
            if (MoveState == "Yes" || MoveState == "yes")
            {
                Zone = "Barren field";  //Moves user towards field
                cout << "You make the long journey back to your beginnings." << endl;
            }
            else if (MoveState == "No" || MoveState == "no")
            {
                cout << "You stay put." << endl;
            }
        }
        else
        {
            cout << "You look confused...";
        }

    }
    else if (Zone == "Cavern")
    {
        if (direction == "Right" || direction == "right")
        {
            checkBag("torch");  //Checks bag for torch
            if (found == false)
            {
                cout << "As you look around you see a flickering, in the corner behind some rocks.\n";
                cout << "You get closer to the source of light and find that there is a hidden torch.\n";
                cout << "You add it to your inventory.\n";
                Inventory.insert(Inventory.end(), "torch");
            }
            else
            {
                cout << "There is nothing along the cave wall.\n";
            }
        }
        else if (direction == "Left" || direction == "left")
        {
            checkBag("torch");  //Checks bag for torch
            if (found == true)
            {
                cout << "The torch you found lights the way and reveals an ancient drawing on the wall.\n\n";
                cout << "               /\\_         \n";
                cout << "            /\\/   \\_\n";
                cout << "           /___/\\____\\ \n";
                cout << "               | |\n";
                cout << "               | |\n";
                cout << "               | |\n";
                cout << "            mmmmmmmmmmmmmmmmmmmmmmmm\n";
                cout << " YYYYYYY____mmmmmmmmmmmmmmmmmmmmmmmm\n";
                cout << " YYYYYYY____mmmmmmmmmmmmmmmmmmmmmmmm\n";
                cout << " YYYYYYY    mmmmmmmmmmmmmmmmmmmmmmmm\n";
                cout << "            mmmmmmmmmmmmmmmmmmmmmmmm\n";
                cout << "               | |\n";
                cout << "               | |\n";
                cout << "               | |\n";
                cout << "_______________| |__________________\n";
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            } else
            {
                cout << "Only darkness lies in front of you. You need a torch to see further." << endl;
            }
        }
        else if (direction == "Forward" || direction == "forward")
        {
            checkBag("torch");
            if (found == true)
            {
                "Your torch shines brightly as you approach a tunnel deep into the mountain.\n";
                cout << "As you dive deeper into the mountain you hear a growl and find a bear defending its cubs.\n";
                cout << "It looks up distressed by the flame held in your hand.\n";
                cout << "Do you battle the bear?(Yes/No)" << endl;
                cin >> BattleState;     //Checks what the user wants to do
                if (BattleState == "Yes" || BattleState == "yes")   //Initiates battle
                {
                    cout << "In one quick movement you put down the torch and ready your " << Equipped[0] << ".\n";
                    Battle();
                }
                else if (BattleState == "No" || BattleState == "no")    //Keeps the user away from the monster
                {
                    cout << "The bear watches as you cower back away from its den." << endl;
                }
            }
            else
            {
                cout << "Darkness surrounds you making it impossible to know where to go. You need a torch.\n";
            }
        }
        else if (direction == "Backward" || direction == "backward")
        {
            cout << "A faint light can be seen from where you entered." << endl;
            cout << "Would you like to leave the cave?(Yes/No)" << endl;
            cin >> MoveState;   //Asks user if they want to move
            if (MoveState == "Yes" || MoveState == "yes")
            {
                Zone = "Mountain";  //Sets user in mountain zone
                cout << "You retreat out of the cavern." << endl;
            }
            else if (MoveState == "No" || MoveState == "no")
            {
                cout << "You stay put." << endl;
            }
        }
        else
        {
            cout << "You look confused...";
        }

    }
}
int main() {
    srand(time(NULL));  //Seed random to time
    string direction;   //variable for direction of user
    Zone = "Barren field";  //Sets the zone the user starts in

    cout << "You awake in an empty and barren field. Next to you is a bronze kite shield, a dagger, a bag, a spike bomb, and two red potions. You put all of the objects in the bag." << endl;

    Inventory.insert(Inventory.end(), "dagger");  //Stores Item
    Equipped[0] = "dagger";     //Equips to weapon slot
    Inventory.insert(Inventory.end(), "kite shield");//Stores Item
    Equipped[1] = "kite shield";    //Equips to shield slot
    Inventory.insert(Inventory.end(), "healing potion");;//Stores Item
    Inventory.insert(Inventory.end(), "healing potion");//Stores Item
    Inventory.insert(Inventory.end(), "spike bomb");//Stores Item
    cout << "You stand up and slowly come to your senses. Where do you look?(Right, Left, Forward, Backward, or Inventory)" << endl;

    while (GameState == true)   //While user is still alive
    {
        if (progress > 0) //Allows for dialogue without repeating initial start
        {
            cout << "Where do you look?(Right, Left, Forward, Backward, or Inventory)" << endl;
        }
        cin >> direction;   //Direction the user would like to look
        Direction(direction);   //Direction function is called to check what happens
        if (progress == 0)
        {
            progress++; //Changes progress so the game knows the start dialogue is over
        }
    }
    return 0;
}