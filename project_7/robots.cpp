// robots.cpp

// Portions you are to complete are marked with a TODO: comment.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Valley::display going.  That
// gives you more flexibility in the order that you tackle the rest of
// the functionality.

#include <cassert>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int NROWS = 10;               // number of rows in the valley
const int NCOLS = 10;               // number of columns in the valley
const int MAXROBOTS = 15;           // max number of robots allowed
const int MAXSOURCES = NROWS*NCOLS; // max number of energy sources
const int FULL_ENERGY = 70;         // number of units when fully charged
const int SHARE_THRESHOLD = 35;     // will share energy if have at least this
const int SHARE_AMOUNT = 10;        // amount of energy to share
const int NORTH = 0;
const int SOUTH = 1;
const int EAST  = 2;
const int WEST  = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declaration
///////////////////////////////////////////////////////////////////////////

void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Valley;  // This is needed to let compiler know that Valley is a type
               //   name, since it's mentioned in the Robot declaration.

class Robot
{
  public:
        // Constructor
    Robot(string nm, Valley* vp, int r, int c, int d);

        // Accessors
    string name() const;
    int    energy() const;
    int    row() const;
    int    col() const;
    int    dir() const;

        // Mutators
    bool   step();

  private:
    string  m_name;
    int     m_energy;
    int     m_row;
    int     m_col;
    int     m_dir;
    Valley* m_valley;
};

class EnergySource
{
  public:
        // Constructor
    EnergySource(int r, int c);

        // Accessors
    int row() const;
    int col() const;

  private:
    int m_row;
    int m_col;
};

class Valley
{
  public:
        // Constructor/destructor
    Valley();
    ~Valley();

        // Accessors
    void   display() const;
    bool   energySourceAt(int r, int c) const;
    Robot* otherRobotAt(Robot* rp) const;
    Robot* getRobotByName(string name) const;

        // Mutators
    bool   addRobot(string name, int r, int c, int d);
    bool   addEnergySource(int r, int c);
    bool   step();

  private:
    Robot*        m_robots[MAXROBOTS];
    int           m_nRobots;
    EnergySource* m_sources[MAXSOURCES];
    int           m_nSources;
    int           m_nSteps;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

  // Constructor:  Create a Robot in the Valley pointed to by vp, with
  //    name nm, location (r,c), and direction d.
Robot::Robot(string nm, Valley* vp, int r, int c, int d)
{
        // Since the first character of the Robot's name shows up in the
        // display, there had better be a first character.
    if (nm.size() == 0)
    {
        cout << "***** A robot must have a non-empty name!" << endl;
        exit(1);
    }
    if (r < 0  ||  r >= NROWS  ||  c < 0  ||  c >= NCOLS)
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }

    m_name = nm;
    m_energy = FULL_ENERGY;
    m_row = r;
    m_col = c;
    m_dir = d;
    m_valley = vp;
}

string Robot::name() const
{
    return m_name;
}

// TODO:  TRIVIAL: Implement the other four Robot accessor functions.  These
//        should be trivial.
int Robot::energy() const
{
	return m_energy;
}
int Robot::row() const
{
	return m_row;
}
int Robot::col() const
{
	return m_col;
}
int Robot::dir() const
{
	return m_dir;
}
bool Robot::step()
{
      // If the robot has no energy left, return false
    // TODO:  Implement this
	if (m_energy==0)
		return false;
      // Otherwise,
      //    Randomly change direction with probability 1/3
    if (rand() % 3 == 0)     // 1/3 probability to pick a direction
        m_dir = rand() % 4;  // pick a random direction (0 through 3)

      //    Attempt to move one step in the direction we're currently facing.
      //      (E.g., to move north, decrement the row coordinate.)  If we can't
      //      move in that direction, don't move.
    switch (m_dir)
    {
      case NORTH:
          // TODO:  Move one step north, if possible
		  if(m_row > 0)
			  m_row--;
        break;
      case SOUTH:
		  if(m_row<NROWS-1)
			  m_row++;
		  break;
      case WEST:
		  if(m_col>0)
			  m_col--;
		  break;
      case EAST:
		  if(m_col<NCOLS-1)
			  m_col++;
          // TODO:  Implement the other movements
        break;
    }

	m_energy--;
	if((*m_valley).energySourceAt(m_row, m_col))
		m_energy=FULL_ENERGY;
      //    The attempt to move consumes one unit of energy.
      //    If as a result of the attempt to move, the robot is at an energy
      //       source, it's recharged to the FULL_ENERGY level.
    // TODO:  Implement this
    
      //    Pick one other robot at this location, if any.  If there is such a
      //       robot, and its energy level is 0, then if we have at least
      //       SHARE_THRESHOLD units of energy, transfer SHARE_AMOUNT units
      //       to that other robot.  (If there's more than one other robot at
      //       this spot who need energy, then the one(s) we don't select are
      //       out of luck:  we don't check them to see if they need a donation.)
    // TODO:  Implement this
	Robot* otherRobot = (*m_valley).otherRobotAt(this);
	if(otherRobot != NULL && (*otherRobot).energy() ==0 && m_energy >= SHARE_THRESHOLD){
		otherRobot->m_energy=SHARE_AMOUNT;
		m_energy-=SHARE_AMOUNT;
	}
      //    Return true, indicating the robot attempted to move.
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  EnergySource implementation
///////////////////////////////////////////////////////////////////////////

EnergySource::EnergySource(int r, int c)
{
    if (r < 0  ||  r >= NROWS  ||  c < 0  ||  c >= NCOLS)
    {
        cout << "**** EnergySource created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_row = r;
    m_col = c;
}

int EnergySource::row() const
{
    return m_row;
}

int EnergySource::col() const
{
    return m_col;
}

///////////////////////////////////////////////////////////////////////////
//  Valley implementation
///////////////////////////////////////////////////////////////////////////

Valley::Valley()
{
    m_nRobots = 0;
    m_nSources = 0;
    m_nSteps = 0;
}

Valley::~Valley()
{
    // Delete any dynamically allocated objects held by the Valley.
      // TODO:  Implement this
	
	//delete m_sources;
	//delete m_robots;
	for(int k=0;k<m_nRobots;k++){
		delete m_robots[k];
	}
	for(int j=0;j<m_nSources;j++)
		delete m_sources[j];
	
}

void Valley::display() const
{
    char grid[NROWS][NCOLS];
    int r, c;
    
      // fill the grid with dots
    for (r = 0; r < NROWS; r++)
        for (c = 0; c < NCOLS; c++)
            grid[r][c] = '.';

      // Mark each energy source with a star
    for (int k = 0; k < m_nSources; k++)
    {
        EnergySource* esp = m_sources[k];
        grid[esp->row()][esp->col()] = '*';
    }

      // TODO:  indicate each robot's position
    // for each robot in the valley,
    //   set the appropriate element of the grid to the first character
    //          of the robot's name.
	for(int k=0; k<m_nRobots;k++)
	{
		grid[(*m_robots[k]).row()][(*m_robots[k]).col()]=(*m_robots[k]).name()[0];
	}

      // Draw the grid
    clearScreen();
    for (r = 0; r < NROWS; r++)
    {
        for (c = 0; c < NCOLS; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
	for(int k=0; k<m_nRobots;k++)
	{
		cout << (*m_robots[k]).name() << " has " << (*m_robots[k]).energy() << " energy units left" <<endl;
	}
      // TODO:  Write robot energy info
    // for each robot in the valley,
    //   write the robot's name and remaining energy level.

    cout << endl << m_nSteps << " steps taken" << endl;
}

bool Valley::energySourceAt(int r, int c) const
{
    // If there is an energy source at coordinates (r,c), return true;
    // otherwise, return false.
      // TODO:  Implement this
	for(int k=0; k< m_nSources;k++)
	{
		if((*m_sources[k]).row()==r)
			if ((*m_sources[k]).col()==c)
				return true;
	}
	return false; // This is here for now just so this will compile.
}

Robot* Valley::otherRobotAt(Robot* rp) const
{
    // If there is at least one robot (other than the one rp points to)
    // at the same (r,c) coordinates as the one rp points to, return a
    // pointer to the one of those other robots with the least amount
    // of energy remaining (if there's a tie, any one of the tied robots
    // will do); otherwise, return NULL.
      // TODO:  Implement this
	Robot* pointer=NULL;
	int lowerEnergy= FULL_ENERGY;
	for(int k=0; k<m_nRobots;k++)
	{
		if((*m_robots[k]).row()==(*rp).row())
			if((*m_robots[k]).col()==(*rp).col())
				if(rp != m_robots[k])
					if((*m_robots[k]).energy()<lowerEnergy){
						lowerEnergy=(*m_robots[k]).energy();
						pointer = m_robots[k];
					}
		if(k==m_nRobots-1)
			return pointer;
	}
	return NULL;// This is here for now just so this will compile.
}

Robot* Valley::getRobotByName(string name) const
{
    // This function is not useful for any purpose other than making it
    // easier for your program to be tested.

    // Return a pointer to the robot with the given name.  (If there are
    // more than one, any one with that will do.)  Return NULL if there is
    // no such robot.
      // TODO:  Implement this
	for(int k=0; k<m_nRobots; k++)
	{
		if((*m_robots[k]).name()==name){
			Robot* namePointer=m_robots[k];
			return namePointer;
		}
	}


    return NULL; // This is here for now just so this will compile.
}

bool Valley::addRobot(string name, int r, int c, int d)
{
    if (r < 0  ||  r >= NROWS  ||  c < 0  ||  c >= NCOLS)
        return false;
	if(m_nRobots==MAXROBOTS)
		return false;
	m_robots[m_nRobots]=new Robot(name,this, r, c, d);
	m_nRobots++;
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot whose name is name, at coordinates
    // (r,c) facing in direction d.  Save the pointer to the newly
    // allocated robot and return true.
      // TODO:  Implement this


    return true;
}

bool Valley::addEnergySource(int r, int c)
{
    if (r < 0  ||  r >= NROWS  ||  c < 0  ||  c >= NCOLS  ||
                        energySourceAt(r, c)  ||  m_nSources == MAXSOURCES)
        return false;
    m_sources[m_nSources] = new EnergySource(r, c);
    m_nSources++;
    return true;
}

bool Valley::step()
{
    m_nSteps++;
	bool movement=false;
	for(int k=0; k<m_nRobots;k++)
	{
		if((*m_robots[k]).step())
			movement=true;
	}

    // Have each robot in the valley step.  If any of them attempted to move,
    // return true.  If none of them did, they're all dead, so return false.
      // TODO:  Implement this

    return movement; // This is here for now just so this will compile.
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
     else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

// You can use whatever main routine you want.  In fact, try different
// things that will thoroughly test your classes.  This main routine is
// the one that the sample executable uses.

int main()
{
        // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

        // Create a valley
    Valley v;

        // Populate it with three robots
    v.addRobot("Abner", 0, 0, SOUTH);
    v.addRobot("Betty", 9, 9, NORTH);
    v.addRobot("Chris", 0, 9, SOUTH);
	
    
        // Add energy sources at (2,2), (2,5), (2,8), (5,2), ..., (8,8)
    for (int r = 2; r < NROWS; r += 3)
        for (int c = 2; c < NCOLS; c += 3)
            v.addEnergySource(r, c);

        // Step until all robots are dead, displaying the valley each time
    do
    {
        v.display();
        cout << endl;
        cout << "Press Enter to continue ";
        cin.ignore(10000, '\n');
    } while(v.step());

    cout << "All robots are dead" << endl;
}