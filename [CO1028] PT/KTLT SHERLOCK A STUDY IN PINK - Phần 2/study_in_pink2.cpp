#include "study_in_pink2.h"
//*                       _oo0oo_
//*                      o8888888o
//*                      88" . "88
//*                      (| -_- |)
//*                      0\  =  /0
//*                    ___/`---'\___
//*                  .' \\|     |// '.
//*                 / \\|||  :  |||// \
//*                / _||||| -:- |||||- \
//*               |   | \\\  -  /// |   |
//*               | \_|  ''\---/''  |_/ |
//*               \  .-\__  '-'  ___/-. /
//*             ___'. .'  /--.--\  `. .'___
//*          ."" '<  `.___\_<|>_/___.' >' "".
//*         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//*         \  \ `_.   \_ __\ /__ _/   .-` /  /
//*     =====`-.____`.___ \_____/___.-`___.-'=====
//*                       `=---='
//*
//*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//*            Phật phù hộ, không bao giờ BUG
//*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//*     g++ -o main main.cpp study_in_pink2.cpp -I . -std=c++11

// 1.Sherlock moving
// 2.Watson moving
// 3.Criminal, Sherlock and Watson moving respectively (In this situation, we don't create robot
//* 4.Configuration
// 5.Criminal, Sherlock, Watson and RobotC moving respectively
// 6.Criminal, Sherlock, Watson and RobotS moving respectively
// 7.Criminal, Sherlock, Watson and RobotW moving respectively
// 8.Criminal, Sherlock, Watson and RobotSW moving respectively
// 9.Activities with Sherlock's Bag
// 10.Activities with Watson's Bag
// 11.Run the StudyInPink program

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
/////
int MakeRound(double x)
{
    if (((double)x) - ((int)x) > 0)
        return (x + 0.99999);
    return ((int)x);
}
int ABS(int x, int y)
{
    if (x > y)
        return x - y;
    return y - x;
}
const Position Position::npos = Position(-1, -1);
MapElement::MapElement(ElementType in_type) { this->type = in_type; }
MapElement::~MapElement() {}
ElementType MapElement::getType() const { return type; }
Path::Path() : MapElement(PATH) {}
Wall::Wall() : MapElement(WALL) {}
FakeWall::FakeWall(int in_req_exp) : MapElement(ElementType::FAKE_WALL) { this->req_exp = in_req_exp; }
int FakeWall::getReqExp() const { return req_exp; }
Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const string &str_pos)
{
    int comma = str_pos.find(',');
    this->r = stoi(str_pos.substr(1, comma - 1));
    this->c = stoi(str_pos.substr(comma + 1, str_pos.length() - comma - 2));
}

int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { this->r = r; }
void Position::setCol(int c) { this->c = c; }
string Position::str() const
{
    return "(" + to_string(r) + "," + to_string(c) + ")";
}
bool Position::isEqual(Position position) const
{
    return (r == position.getRow() && c == position.getCol());
}

bool Position::isEqual(int in_r, int in_c) const
{
    return (r == in_r && c == in_c);
}
MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name)
    : index(index), pos(pos), map(map), name(name) {}

MovingObject::~MovingObject(){};
Position MovingObject::getCurrentPosition() const
{
    return pos;
}

Character::Character(int index, const Position pos, Map *map, const string &name)
    : MovingObject(index, pos, map, name) {}

Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp < 0 ? 0 : (init_hp > 500 ? 500 : init_hp)), exp(init_exp < 0 ? 0 : (init_exp > 900 ? 900 : init_exp)), index_moving_rule(0) {}

Position Sherlock::getNextPosition()
{
    if (map == nullptr || moving_rule.empty())
        return Position::npos;
    char direction = moving_rule[index_moving_rule];
    int next_row = pos.getRow();
    int next_col = pos.getCol();

    if (direction == 'L')
    {
        next_col--;
    }
    else if (direction == 'R')
    {
        next_col++;
    }
    else if (direction == 'U')
    {
        next_row--;
    }
    else if (direction == 'D')
    {
        next_row++;
    }
    else
    {
        return Position::npos;
    }
    Position next_pos(next_row, next_col);
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    else
    {
        return Position::npos;
    }
}
void Sherlock::move()
{
    Position nextPos = getNextPosition();

    if ((!nextPos.isEqual(Position::npos)))
    {
        pos = nextPos;
    }
    index_moving_rule = (index_moving_rule + 1) % moving_rule.size();
}
string Sherlock::str() const
{
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

MovingObjectType Sherlock::getObjectType() const
{
    return MovingObjectType::SHERLOCK;
}

int Sherlock::getHP() const { return hp; }
int Sherlock::getEXP() const { return exp; }
void Sherlock::setHP(int HP)
{
    hp = (HP < 0) ? 0 : (HP > 500) ? 500
                                   : HP;
}

void Sherlock::setEXP(int EXP)
{
    exp = (EXP < 0) ? 0 : (EXP > 900) ? 900
                                      : EXP;
}

Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), hp(init_hp < 0 ? 0 : (init_hp > 500 ? 500 : init_hp)), exp(init_exp < 0 ? 0 : (init_exp > 900 ? 900 : init_exp)), index_moving_rule(0) {}

Position Watson::getNextPosition()
{
    if (map == nullptr || moving_rule.empty())
        return Position::npos;
    char direction = moving_rule[index_moving_rule];
    int next_row = pos.getRow();
    int next_col = pos.getCol();

    if (direction == 'L')
    {
        next_col--;
    }
    else if (direction == 'R')
    {
        next_col++;
    }
    else if (direction == 'U')
    {
        next_row--;
    }
    else if (direction == 'D')
    {
        next_row++;
    }
    else
    {
        return Position::npos;
    }

    Position next_pos(next_row, next_col);
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    else
    {
        return Position::npos;
    }
}

void Watson::move()
{
    Position nextPos = getNextPosition();

    if ((!nextPos.isEqual(Position::npos)))
    {
        pos = nextPos;
    }
    index_moving_rule = (index_moving_rule + 1) % moving_rule.size();
}
string Watson::str() const
{
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

MovingObjectType Watson::getObjectType() const
{
    return MovingObjectType::WATSON;
}

int Watson::getHP() const { return hp; }

int Watson::getEXP() const { return exp; }

void Watson::setHP(int HP)
{
    hp = (HP < 0) ? 0 : (HP > 500) ? 500
                                   : HP;
}

void Watson::setEXP(int EXP)
{
    exp = (EXP < 0) ? 0 : (EXP > 900) ? 900
                                      : EXP;
}

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
{
    map = new MapElement **[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; j++)
        {
            map[i][j] = new Path();
        }
    }

    for (int i = 0; i < num_walls; i++)
    {
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        if (r >= 0 && r < num_rows && c >= 0 && c < num_cols)
        {
            map[r][c] = new Wall();
        }
    }

    for (int i = 0; i < num_fake_walls; i++)
    {
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        if (r >= 0 && r < num_rows && c >= 0 && c < num_cols)
        {
            ElementType type = map[r][c]->getType();
            if (type == WALL)
            {
                map[r][c] == new Wall();
            }
            else
            {
                map[r][c] = new FakeWall((r * 257 + c * 139 + 89) % 900 + 1);
            }
        }
    }
}
Map::~Map()
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}

int Map::getNumRows() const { return num_rows; }
int Map::getNumCols() const { return num_cols; }
bool Map::isValid(const Position pos, MovingObject *mv_obj) const
{
    int i = pos.getRow();
    int j = pos.getCol();

    if (i >= 0 && i < num_rows && j >= 0 && j < num_cols)
    {
        ElementType type = map[i][j]->getType();
        MovingObjectType objectType = mv_obj->getObjectType();

        if (type == PATH || type == FAKE_WALL)
        {
            if (objectType == SHERLOCK || objectType == CRIMINAL || objectType == ROBOT)
            {
                return true;
            }
            else if (objectType == WATSON)
            {
                Watson *watson = dynamic_cast<Watson *>(mv_obj);
                int exp = watson->getEXP();

                if (type == PATH || exp >= dynamic_cast<FakeWall *>(map[i][j])->getReqExp())
                {
                    return true;
                }
            }
        }
        else if (type == WALL)
            return false;
    }
    return false;
}

int Criminal::ManDis(const Position &pos1, const Position &pos2) const
{
    int x1 = pos1.getRow();
    int y1 = pos1.getCol();
    int x2 = pos2.getRow();
    int y2 = pos2.getCol();
    return ABS(x1, x2) + ABS(y1, y2);
}
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "Criminal")
{
    this->sherlock = sherlock;
    this->watson = watson;
    this->count = 0;
}
Position Criminal::getNextPosition()
{
    if (map == nullptr)
        return Position::npos;

    Position max_distance_position = Position::npos;
    int max_manhattan_distance = INT_MIN;

    // Array to represent directions: up, left, down, right
    int direction[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < 4; i++)
    {
        int next_row = pos.getRow() + direction[i][0];
        int next_col = pos.getCol() + direction[i][1];
        Position next_position(next_row, next_col);

        // Check if the next position is valid
        if (!map->isValid(next_position, this))
            continue;

        // Calculate distances to Sherlock and Watson
        int distance_to_sherlock = ManDis(next_position, sherlock->getCurrentPosition());
        int distance_to_watson = ManDis(next_position, watson->getCurrentPosition());
        int total_distance = distance_to_sherlock + distance_to_watson;

        // Update max distance and position if necessary
        if (total_distance > max_manhattan_distance)
        {
            max_manhattan_distance = total_distance;
            max_distance_position = next_position;
        }
    }
    return max_distance_position;
}

Position Criminal::getPreviousPosition() { return pre_pos; }
void Criminal::move()
{
    pre_pos = getCurrentPosition();

    Position nextPos = getNextPosition();
    if (!nextPos.isEqual(Position::npos))
    {
        pos = nextPos;
        count++;
    }
}

string Criminal::str() const
{
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

MovingObjectType Criminal::getObjectType() const
{
    return MovingObjectType::CRIMINAL;
}
int Criminal::getCountStep() const
{
    return count;
}
bool Criminal::isCreatedRobotNext() const
{
    int step = getCountStep();
    if (step > 0 && step % 3 == 0)
        return true;
    else
        return false;
}

Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), robot_type(robot_type), criminal(criminal) {}

Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    Position criminal_pos = criminal->getCurrentPosition();
    RobotType robot_type;
    int count = criminal->getCountStep();

    if (count == 2)
    {
        robot_type = RobotType::C;
        return new RobotC(index, criminal_pos, map, robot_type, criminal);
    }
    else
    {
        int distance_to_sherlock = criminal->ManDis(criminal_pos, sherlock->getCurrentPosition());
        int distance_to_watson = criminal->ManDis(criminal_pos, watson->getCurrentPosition());

        if (distance_to_sherlock < distance_to_watson)
        {
            robot_type = RobotType::S;
            return new RobotS(index, criminal_pos, map, criminal, sherlock);
        }
        else if (distance_to_sherlock > distance_to_watson)
        {
            robot_type = RobotType::W;
            return new RobotW(index, criminal_pos, map, criminal, watson);
        }
        else
        {
            robot_type = RobotType::SW;
            return new RobotSW(index, criminal_pos, map, criminal, sherlock, watson);
        }
    }
}
MovingObjectType Robot::getObjectType() const
{
    return MovingObjectType::ROBOT;
}

RobotC::RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal)
    : Robot(index, init_pos, map, robot_type, criminal, "RobotC") {}
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
    : Robot(index, init_pos, map, robot_type, criminal, "RobotC") {}
int RobotC::getDistance(Sherlock *sherlock)
{
    return criminal->ManDis(criminal->getCurrentPosition(), sherlock->getCurrentPosition());
}

int RobotC::getDistance(Watson *watson)
{
    return criminal->ManDis(criminal->getCurrentPosition(), watson->getCurrentPosition());
}
Position RobotC::getNextPosition()
{
    int x = this->getCurrentPosition().getRow();
    int y = this->getCurrentPosition().getCol();
    if (map->isValid(Position(x, y - 1), this) ||
        map->isValid(Position(x, y + 1), this) ||
        map->isValid(Position(x - 1, y), this) ||
        map->isValid(Position(x + 1, y), this))
        ;
    else
        return Position::npos;
    Position next_pos_c = criminal->getCurrentPosition();
    if (map->isValid(next_pos_c, this))
        return next_pos_c;
    return Position::npos;
}
void RobotC::move()
{
    Position nextPos = criminal->getPreviousPosition();

    if (!nextPos.isEqual(Position::npos))
    {
        pos = nextPos;
    }
}
string RobotC::str() const
{
    return "Robot[pos=" + pos.str() + ";type=C;dist=]";
}
int RobotC::getDistance() const
{
    return 0;
}
RobotType RobotC::getType() const
{
    return RobotType::C;
}

RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal, "RobotW")
{
    this->watson = watson;
}

Position RobotW::getNextPosition()
{
    if (map == nullptr)
        return Position::npos;

    Position nearest_wat = Position::npos;
    int nearest_distance = INT_MAX;
    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < 4; i++)
    {
        int next_row = pos.getRow() + direction[i][0];
        int next_col = pos.getCol() + direction[i][1];
        Position next_position(next_row, next_col);

        if (!map->isValid(next_position, this))
            continue;

        int distance_to_watson = criminal->ManDis(next_position, watson->getCurrentPosition());

        if (distance_to_watson < nearest_distance)
        {
            nearest_distance = distance_to_watson;
            nearest_wat = next_position;
        }
    }

    return nearest_wat;
}

void RobotW::move()
{
    Position nextPos = getNextPosition();

    if (!nextPos.isEqual(Position::npos))
    {
        pos = nextPos;
    }
}

string RobotW::str() const
{
    return "Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(getDistance()) + "]";
}

RobotType RobotW::getType() const
{
    return RobotType::W;
}

int RobotW::getDistance() const
{
    return criminal->ManDis(pos, watson->getCurrentPosition());
}

RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock)
    : Robot(index, init_pos, map, robot_type, criminal, "RobotS")
{
    this->sherlock = sherlock;
}

Position RobotS::getNextPosition()
{
    if (map == nullptr)
        return Position::npos;

    Position nearest_wat = Position::npos;
    int nearest_distance = INT_MAX;
    int distance[4];
    Position distance_pos[4];
    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < 4; i++)
    {
        int next_row = pos.getRow() + direction[i][0];
        int next_col = pos.getCol() + direction[i][1];
        Position next_position(next_row, next_col);
        int distance_to_sherlock = criminal->ManDis(next_position, sherlock->getCurrentPosition());

        distance[i] = distance_to_sherlock;
        distance_pos[i] = next_position;
        if (map->isValid(distance_pos[i], this) == false)
        {
            distance_pos[i] = Position::npos;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (distance_pos[i].isEqual(Position::npos) == false)
        {
            if (distance[i] < nearest_distance)
            {
                nearest_distance = distance[i];
                nearest_wat.setRow(distance_pos[i].getRow());
                nearest_wat.setCol(distance_pos[i].getCol());
            }
            else if (distance[i] == nearest_distance)
            {
                if (i == 0)
                {
                    nearest_wat.setRow(distance_pos[i].getRow());
                    nearest_wat.setCol(distance_pos[i].getCol());
                }
                else if (i == 1)
                {
                    if (distance[i] < distance[0])
                    {
                        nearest_wat.setRow(distance_pos[i].getRow());
                        nearest_wat.setCol(distance_pos[i].getCol());
                    }
                }
                else if (i == 2)
                {
                    if (distance[i] < distance[0] && distance[i] < distance[1])
                    {
                        nearest_wat.setRow(distance_pos[i].getRow());
                        nearest_wat.setCol(distance_pos[i].getCol());
                    }
                }
            }
        }
    }
    return nearest_wat;
}
void RobotS::move()
{
    Position nextPos = getNextPosition();
    if (map->isValid(nextPos, this))
    {
        pos = nextPos;
    }
}

string RobotS::str() const
{
    return "Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) + "]";
}

RobotType RobotS::getType() const
{
    return RobotType::S;
}

int RobotS::getDistance() const
{
    return criminal->ManDis(pos, sherlock->getCurrentPosition());
}

RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal, "RobotSW")
{
    this->sherlock = sherlock;
    this->watson = watson;
}
Position RobotSW::getNextPosition()
{
    if (map == nullptr)
        return Position::npos;

    Position nearest_distance_pos = Position::npos;
    int nearest_distance = INT_MAX;
    int distance[4];
    Position distance_pos[4];
    int direction[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};

    for (int i = 0; i < 4; i++)
    {
        int next_row = pos.getRow() + direction[i][0];
        int next_col = pos.getCol() + direction[i][1];
        Position next_position(next_row, next_col);
        int distance_to_sherlock = criminal->ManDis(next_position, sherlock->getCurrentPosition());
        int distance_to_watson = criminal->ManDis(next_position, watson->getCurrentPosition());
        int total_distance = distance_to_sherlock + distance_to_watson;

        distance[i] = total_distance;
        distance_pos[i] = next_position;
        if (map->isValid(distance_pos[i], this) == false)
        {
            distance_pos[i] = Position::npos;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (distance_pos[i].isEqual(Position::npos) == false)
        {
            if (distance[i] < nearest_distance)
            {
                nearest_distance = distance[i];
                nearest_distance_pos = distance_pos[i];
            }
            else if (distance[i] == nearest_distance)
            {
                if (i == 0)
                {
                    nearest_distance_pos = distance_pos[i];
                }
                else if (i == 1)
                {
                    if (distance[i] < distance[0])
                    {
                        nearest_distance_pos = distance_pos[i];
                    }
                }
                else if (i == 2)
                {
                    if (distance[i] < distance[0] && distance[i] < distance[1])
                    {
                        nearest_distance_pos = distance_pos[i];
                    }
                }
            }
        }
    }
    return nearest_distance_pos;
}
string RobotSW::str() const
{
    int x = criminal->ManDis(pos, sherlock->getCurrentPosition());
    int y = criminal->ManDis(pos, watson->getCurrentPosition());
    return "Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(x + y) + "]";
}
RobotType RobotSW::getType() const
{
    return RobotType::SW;
}
int RobotSW::getDistance() const
{
    int x = criminal->ManDis(pos, sherlock->getCurrentPosition());
    int y = criminal->ManDis(pos, watson->getCurrentPosition());
    return x + y;
}
void RobotSW::move()
{
    Position nextPos = getNextPosition();
    if (map->isValid(nextPos, this))
    {
        pos = nextPos;
    }
}

ArrayMovingObject::ArrayMovingObject(int capacity)
{
    this->capacity = capacity;
    this->count = 0;
    arr_mv_objs = new MovingObject *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        arr_mv_objs[i] = nullptr;
    }
}
ArrayMovingObject::~ArrayMovingObject()
{
    delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    if (!isFull())
    {
        arr_mv_objs[count] = mv_obj;
        count++;
        return true;
    }
    return false;
}
MovingObject *ArrayMovingObject::get(int index) const
{
    if (index >= 0 && index < count)
    {
        return arr_mv_objs[index];
    }
    return nullptr;
}

int ArrayMovingObject::size() const
{
    return count;
}

string ArrayMovingObject::str() const
{
    string res = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
    for (int i = 0; i < count; i++)
    {
        if (arr_mv_objs[i] != nullptr)
        {
            res += arr_mv_objs[i]->str();
            if (i != count - 1)
            {
                res += ";";
            }
        }
    }
    res += "]";
    return res;
}

Configuration::Configuration(const string &filepath)
{
    ifstream f(filepath);
    string line;
    while (f >> line)
    {
        int pos = line.find('=');

        if (pos != string::npos)
        {
            string check = line.substr(0, pos);
            string value = line.substr(pos + 1);

            if (check == "MAP_NUM_ROWS")
            {
                map_num_rows = stoi(value);
            }
            else if (check == "MAP_NUM_COLS")
            {
                map_num_cols = stoi(value);
            }
            else if (check == "MAX_NUM_MOVING_OBJECTS")
            {
                max_num_moving_objects = stoi(value);
            }
            else if (check == "ARRAY_WALLS")
            {
                value = value.substr(1, value.length() - 2);
                int num_pair = 0;
                int start = 0;
                int end = value.find(',', start);
                while (end != string::npos)
                {
                    num_pair++;
                    start = end + 1;
                    end = value.find(',', start);
                }
                num_walls = num_pair;
                arr_walls = new Position[num_walls];
                start = 1;
                end = value.find(')');
                int i = 0;
                while (end != string::npos)
                {
                    string pair = value.substr(start, end - start);
                    int comma = pair.find(',');
                    string tocomma = pair.substr(0, comma);
                    string aftercomma = pair.substr(comma + 1);
                    int x = stoi(tocomma), y = stoi(aftercomma);
                    arr_walls[i].setRow(x);
                    arr_walls[i].setCol(y);
                    start = end + 3;
                    end = value.find(')', start);
                    i++;
                }
            }
            else if (check == "ARRAY_FAKE_WALLS")
            {
                value = value.substr(1, value.length() - 2);
                int num_pair = 0, start = 0;
                int end = value.find(',', start);
                while (end != string::npos)
                {
                    num_pair++;
                    start = end + 1;
                    end = value.find(',', start);
                }
                num_fake_walls = num_pair;
                arr_fake_walls = new Position[num_fake_walls];
                start = 1;
                end = value.find(')');
                int i = 0;
                while (end != string::npos)
                {
                    string pair = value.substr(start, end - start);
                    int comma = pair.find(',');
                    string tocomma = pair.substr(0, comma);
                    string aftercomma = pair.substr(comma + 1);
                    int x = stoi(tocomma);
                    int y = stoi(aftercomma);
                    arr_fake_walls[i].setRow(x);
                    arr_fake_walls[i].setCol(y);
                    start = end + 3;
                    end = value.find(')', start);
                    i++;
                }
            }
            else if (check == "SHERLOCK_MOVING_RULE")
            {
                sherlock_moving_rule = value;
            }
            else if (check == "SHERLOCK_INIT_POS")
            {
                int start = value.find('(');
                int comma = value.find(',');
                int end = value.find(')');
                string tocomma = value.substr(start + 1, comma - 1);
                string aftercomma = value.substr(comma + 1, end - comma - 1);
                int x = stoi(tocomma);
                int y = stoi(aftercomma);
                sherlock_init_pos.setRow(x);
                sherlock_init_pos.setCol(y);
            }
            else if (check == "SHERLOCK_INIT_HP")
            {
                sherlock_init_hp = stoi(value);
            }
            else if (check == "SHERLOCK_INIT_EXP")
            {
                sherlock_init_exp = stoi(value);
            }
            else if (check == "WATSON_MOVING_RULE")
            {
                watson_moving_rule = value;
            }
            else if (check == "WATSON_INIT_POS")
            {
                // Tìm vị trí của dấu mở ngoặc đầu tiên, dấu phẩy, và dấu đóng ngoặc
                int start = value.find('(');
                int comma = value.find(',');
                int end = value.find(')');

                // Trích xuất chuỗi trước và sau dấu phẩy
                string tocomma = value.substr(start + 1, comma - start - 1);
                string aftercomma = value.substr(comma + 1, end - comma - 1);

                // Chuyển chuỗi thành số nguyên và gán vào biến x và y
                int x = stoi(tocomma);
                int y = stoi(aftercomma);

                // Gán giá trị x và y vào watson_init_pos
                watson_init_pos.setRow(x);
                watson_init_pos.setCol(y);
            }

            else if (check == "WATSON_INIT_HP")
            {
                watson_init_hp = stoi(value);
            }
            else if (check == "WATSON_INIT_EXP")
            {
                watson_init_exp = stoi(value);
            }
            else if (check == "CRIMINAL_INIT_POS")
            {

                int start = value.find('(');
                int comma = value.find(',');
                int end = value.find(')');

                string tocomma = value.substr(start + 1, comma - start - 1);
                string aftercomma = value.substr(comma + 1, end - comma - 1);

                int x = stoi(tocomma);
                int y = stoi(aftercomma);

                criminal_init_pos.setRow(x);
                criminal_init_pos.setCol(y);
            }

            else if (check == "NUM_STEPS")
            {
                num_steps = stoi(value);
            }
        }
    }
}

Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}
string Configuration::str() const
{
    string ketqua = "Configuration[\n";
    ketqua += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
    ketqua += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
    ketqua += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
    ketqua += "NUM_WALLS=" + to_string(num_walls) + "\n";
    ketqua += "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; i++)
    {
        ketqua += "(" + to_string(arr_walls[i].getRow()) + "," + to_string(arr_walls[i].getCol()) + ")";
        if (i < num_walls - 1)
        {
            ketqua += ";";
        }
    }
    ketqua += "]\n";
    ketqua += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
    ketqua += "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; i++)
    {
        ketqua += "(" + to_string(arr_fake_walls[i].getRow()) + "," + to_string(arr_fake_walls[i].getCol()) + ")";
        if (i < num_fake_walls - 1)
        {
            ketqua += ";";
        }
    }
    ketqua += "]\nSHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
    ketqua += "SHERLOCK_INIT_POS=(" + to_string(sherlock_init_pos.getRow()) + "," + to_string(sherlock_init_pos.getCol()) + ")\n";
    ketqua += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
    ketqua += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
    ketqua += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
    ketqua += "WATSON_INIT_POS=(" + to_string(watson_init_pos.getRow()) + "," + to_string(watson_init_pos.getCol()) + ")\n";
    ketqua += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
    ketqua += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
    ketqua += "CRIMINAL_INIT_POS=(" + to_string(criminal_init_pos.getRow()) + "," + to_string(criminal_init_pos.getCol()) + ")\n";
    ketqua += "NUM_STEPS=" + to_string(num_steps) + "\n]";
    return ketqua;
}
StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}
bool StudyPinkProgram::isStop() const
{
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) || watson->getHP() == 1 || sherlock->getHP() == 1)
    {
        return true;
    }
    else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
    {
        return true;
    }
    else if (sherlock->getHP() == 1 || watson->getHP() == 1)
    {
        return true;
    }
    return false;
}
StudyPinkProgram::~StudyPinkProgram()
{
    delete config;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
    delete arr_mv_objs;
}

ItemType MagicBook::getType() const { return ItemType::MAGIC_BOOK; }
string MagicBook::str() const { return "MagicBook"; }
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    if (obj && !robot)
    {
        if (Sherlock *sherlock = dynamic_cast<Sherlock *>(obj))
        {
            return (sherlock->getEXP() <= 350);
        }
        else if (Watson *watson = dynamic_cast<Watson *>(obj))
        {
            return (watson->getEXP() <= 350);
        }
    }
    return false;
}

void MagicBook::use(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);

    if ((sherlock || watson) && robot == nullptr)
    {
        if (sherlock && sherlock->getEXP() <= 350)
            sherlock->setEXP(MakeRound((sherlock->getEXP()) * 1.25));
        if (watson && (watson->getEXP()) <= 350)
            watson->setEXP(MakeRound((watson->getEXP()) * 1.25));
    }
}
ItemType EnergyDrink::getType() const { return ItemType::ENERGY_DRINK; }
string EnergyDrink::str() const { return "EnergyDrink"; }
bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);

    if ((sherlock || watson) && robot == nullptr)
    {
        if (sherlock && sherlock->getHP() <= 100)
        {
            return true;
        }
        if (watson && watson->getHP() <= 100)
        {
            return true;
        }
    }
    return false;
}
void EnergyDrink::use(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);

    if ((sherlock || watson) && robot == nullptr)
    {
        if (sherlock && sherlock->getHP() <= 100)
            sherlock->setHP(MakeRound(sherlock->getHP() * 1.2));
        if (watson && watson->getHP() <= 100)
            watson->setHP(MakeRound(watson->getHP() * 1.2));
    }
}
ItemType FirstAid::getType() const { return ItemType::FIRST_AID; }
string FirstAid::str() const { return "FirstAid"; }
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);

    if ((sherlock || watson) && robot == nullptr)
    {
        if (sherlock && (sherlock->getEXP() <= 350 || sherlock->getHP() <= 100))
            return true;
        if (watson && (watson->getEXP() <= 350 || watson->getHP() <= 100))
            return true;
    }
    return false;
}
void FirstAid::use(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);

    if ((sherlock || watson) && robot == nullptr)
    {
        if (sherlock && (sherlock->getEXP() <= 350 || sherlock->getHP() <= 100))
            sherlock->setHP(MakeRound(sherlock->getHP() * 1.5));
        if (watson && (watson->getEXP() <= 350 || watson->getHP() <= 100))
            watson->setHP(MakeRound((watson->getHP()) * 1.5));
    }
}
ItemType ExcemptionCard::getType() const { return ItemType::EXCEMPTION_CARD; }
string ExcemptionCard::str() const { return "ExcemptionCard"; }
bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    if (sherlock && robot != nullptr)
    {
        if (sherlock->getHP() % 2 == 1)
            return true;
    }
    return false;
}
void ExcemptionCard::use(Character *obj, Robot *robot)
{
}
PassingCard::PassingCard(int i, int j)
{
    int t = (i * 11 + j) % 4;
    if (t == 0)
    {
        challenge = "RobotS";
    }
    else if (t == 1)
    {
        challenge = "RobotC";
    }
    else if (t == 2)
    {
        challenge = "RobotSW";
    }
    else if (t == 3)
    {
        challenge = "all";
    }
}

PassingCard::PassingCard(string s) { this->challenge = s; }
ItemType PassingCard::getType() const { return ItemType::PASSING_CARD; }
string PassingCard::str() const
{
    return "PassingCard";
}
bool PassingCard::canUse(Character *obj, Robot *robot)
{
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (watson && robot != nullptr)
    {
        if (watson->getHP() % 2 == 0)
            return true;
    }
    return false;
}
void PassingCard::use(Character *obj, Robot *robot)
{
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (watson || robot != nullptr)
    {
        RobotS *robotS = dynamic_cast<RobotS *>(robot);
        RobotC *robotC = dynamic_cast<RobotC *>(robot);
        RobotSW *robotSW = dynamic_cast<RobotSW *>(robot);
        if (challenge == "all" || (robotS && challenge == "RobotS") || (robotC && challenge == "RobotC") || (robotSW && challenge == "RobotSW"))
        {
        }
        else
        {
            watson->setEXP(watson->getEXP() - 50);
        }
    }
}
BaseBag::BaseBag(int capacity)
{
    this->capacity = capacity;
    this->head = nullptr;
    this->size = 0;
}
BaseBag::~BaseBag()
{
    while (size)
    {
        size--;
        Node *temp = head;
        head = head->next;
        delete temp->item;
        delete temp;
    }
}
bool BaseBag::insert(BaseItem *item)
{
    if (size >= capacity)
        return false;
    Node *newNode = new Node(item, head);
    head = newNode;
    size++;
    return true;
}
BaseItem *BaseBag::get(ItemType itemType)
{
    if (size == 0)
        return nullptr;

    for (Node *current = head; current != nullptr; current = current->next)
    {
        if (current->item->getType() == itemType)
        {
            BaseItem *temp = current->item;
            current->item = head->item;
            head->item = temp;

            Node *tempNode = head->next;
            delete head;
            head = tempNode;

            size--;
            return temp;
        }
    }
    return nullptr;
}
string BaseBag::str() const
{
    string res = "Bag[count=" + to_string(size) + ";";
    Node *current = head;
    while (current)
    {
        res += current->item->str();
        if (current->next)
            res += ",";
        current = current->next;
    }
    res += "]";
    return res;
}
SherlockBag::SherlockBag(Sherlock *character)
    : BaseBag(13)
{
    this->sherlock = character;
}
BaseItem *SherlockBag::get()
{
    if (size == 0)
        return nullptr;

    Node *prev = nullptr;
    Node *current = head;

    // Bước 1: Tìm vật phẩm có thể sử dụng đầu tiên trong túi
    while (current != nullptr)
    {
        if (current->item->canUse(sherlock, nullptr))
        {
            // Bước 2: Tráo vị trí vật phẩm tìm được với vị trí đầu tiên trong túi
            BaseItem *tempItem = current->item;
            current->item = head->item;
            head->item = tempItem;

            // Bước 3: Sử dụng vật phẩm tìm được trước khi xóa
            tempItem->use(sherlock, nullptr);

            // Bước 4: Xóa vị trí và vật phẩm ở vị trí đầu tiên khỏi Node
            if (prev == nullptr)
            {
                head = head->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            size--;
            return tempItem;
        }
        prev = current;
        current = current->next;
    }

    return nullptr;
}

BaseItem *SherlockBag::get(ItemType itemType)
{
    if (size == 0)
        return nullptr;

    Node *prev = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        if (current->item->getType() == itemType && current->item->canUse(sherlock, nullptr))
        {
            if (current != head)
            {
                BaseItem *temp = head->item;
                head->item = current->item;
                current->item = temp;
            }
            Node *tempNode = head->next;
            delete head;
            head = tempNode;

            size--;
            return current->item;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}

WatsonBag::WatsonBag(Watson *character)
    : BaseBag(15)
{
    this->watson = character;
}
BaseItem *WatsonBag::get()
{
    if (size == 0)
        return nullptr;

    Node *prev = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        if (current->item->canUse(watson, nullptr))
        {
            BaseItem *tempItem = current->item;
            current->item = head->item;
            head->item = tempItem;

            Node *tempNode = head;
            if (prev == nullptr)
            {
                head = head->next;
            }
            else
            {
                prev->next = current->next;
            }

            delete tempNode;
            size--;
            return tempItem;
        }
        prev = current;
        current = current->next;
    }

    return nullptr;
}

BaseItem *WatsonBag::get(ItemType itemType)
{
    if (size == 0)
        return nullptr;

    Node *prev = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        if (current->item->getType() == itemType && current->item->canUse(watson, nullptr))
        {
            if (current != head)
            {
                BaseItem *temp = head->item;
                head->item = current->item;
                current->item = temp;
            }
            Node *tempNode = head->next;
            delete head;
            head = tempNode;

            size--;
            return current->item;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////