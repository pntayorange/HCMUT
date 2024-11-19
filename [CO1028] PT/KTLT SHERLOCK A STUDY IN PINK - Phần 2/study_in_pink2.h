/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */
// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int MakeRound(double x);
int ABS(int x, int y);
// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;
class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;
class ArrayMovingObject;
class StudyPinkProgram;
class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C,
    S,
    W,
    SW
};
enum MovingObjectType
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROBOT
};

class MapElement
{
    friend class TestStudyInPink;

protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement
{
    friend class TestStudyInPink;

public:
    Path();
};

class Wall : public MapElement
{
    friend class TestStudyInPink;

public:
    Wall();
};

class FakeWall : public MapElement
{
    friend class TestStudyInPink;

private:
    int req_exp;

public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};
class Map
{
    friend class TestStudyInPink;

private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls); //: num_rows(num_rows), num_cols(num_cols){};
    ~Map();
    int getNumRows() const;
    int getNumCols() const;
    ElementType getElementType(int i, int j) const;
    bool isValid(const Position pos, MovingObject *mv_obj) const;
};
class Position
{
    friend class TestStudyInPink;

private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(Position position) const;
    static const Position npos;
};

class MovingObject
{
    friend class TestStudyInPink;

protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");
    string getname();
    ~MovingObject();
    virtual Position getNextPosition() = 0;
    void setPosition(Position pos)
    {
        this->pos = pos;
    }

    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Character : public MovingObject
{
    friend class TestStudyInPink;

protected:
    int hp;
    int exp;

public:
    Character(int index, const Position pos, Map *map, const string &name = "");
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Sherlock : public Character
{
    friend class TestStudyInPink;

private:
    string moving_rule;
    int hp;
    int exp;
    int index_moving_rule;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition() override;
    void move();
    string str() const;
    MovingObjectType getObjectType() const;

    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
};

class Watson : public Character
{
    friend class TestStudyInPink;

private:
    string moving_rule;
    int hp;
    int exp;
    int index_moving_rule;

public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition() override;
    void move();
    string str() const override;
    MovingObjectType getObjectType() const override;
    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
};

class Criminal : public Character
{
    friend class TestStudyInPink;

private:
    Sherlock *sherlock;
    Watson *watson;
    int count;
    Position pre_pos;

public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    Position getNextPosition() override;
    Position getPreviousPosition();
    void move();
    string str() const;
    MovingObjectType getObjectType() const;
    int getCountStep() const;
    int ManDis(const Position &pos1, const Position &pos2) const;
    bool isCreatedRobotNext() const;
};

class Robot : public MovingObject
{
    friend class TestStudyInPink;

protected:
    Criminal *criminal;
    // BaseItem * item;
    RobotType robot_type;

public:
    Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name = "");
    static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    MovingObjectType getObjectType() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual RobotType getType() const = 0;
    virtual int getDistance() const = 0;
};

class RobotC : public Robot
{
    friend class TestStudyInPink;

public:
    RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal);
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal);
    int getDistance(Sherlock *sherlock);
    int getDistance(Watson *watson);
    Position getNextPosition() override;
    void move();
    string str() const override;
    int getDistance() const override;
    RobotType getType() const override;
};

class RobotW : public Robot
{
    friend class TestStudyInPink;

private:
    Watson *watson;

public:
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getType() const override;
    int getDistance() const override;
};

class RobotS : public Robot
{
    friend class TestStudyInPink;

private:
    Sherlock *sherlock;

public:
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock);
    // RobotS(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock);
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getType() const override;
    int getDistance() const override;
};

class RobotSW : public Robot
{
    friend class TestStudyInPink;

private:
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    // RobotSW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    Position getNextPosition() override;
    string str() const;
    RobotType getType() const override;
    int getDistance() const override;
    void move() override;
};

class ArrayMovingObject
{
    friend class TestStudyInPink;

private:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject *mv_obj);
    MovingObject *get(int index) const;
    int size() const;
    string str() const;
};

class Configuration
{
    friend class TestStudyInPink;
    friend class StudyPinkProgram;

private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
};

class BaseItem
{
    friend class TestStudyInPink;

protected:
    ItemType item_type;
    string passing_card_challenge;

public:
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    virtual void use(Character *obj, Robot *robot) = 0;
    virtual ItemType getType() const = 0;
    virtual string str() const = 0;
    ~BaseItem() {}
};
class MagicBook : public BaseItem
{
    friend class TestStudyInPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    ItemType getType() const;
    string str() const;
};
class EnergyDrink : public BaseItem
{
    friend class TestStudyInPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    ItemType getType() const;
    string str() const;
};
class FirstAid : public BaseItem
{
    friend class TestStudyInPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    ItemType getType() const;
    string str() const;
};
class ExcemptionCard : public BaseItem
{
    friend class TestStudyInPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    ItemType getType() const;
    string str() const;
};
class PassingCard : public BaseItem
{
    friend class TestStudyInPink;

private:
    string challenge;

public:
    PassingCard(int i, int j);
    PassingCard(string s);
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    ItemType getType() const;
    string str() const;
};
class BaseBag
{
    friend class TestStudyInPink;

protected:
    class Node
    {
    public:
        BaseItem *item;
        Node *next;

    public:
        Node(BaseItem *item, Node *next = nullptr) : item(item), next(next) {}
    };

protected:
    int size;
    int capacity;
    Node *head;

public:
    BaseBag(int capacity);
    virtual ~BaseBag();
    virtual bool insert(BaseItem *item);
    virtual BaseItem *get() = 0;
    virtual BaseItem *get(ItemType itemType);
    virtual string str() const;
};
class SherlockBag : public BaseBag
{
    friend class TestStudyInPink;

private:
    Sherlock *sherlock;

public:
    SherlockBag(Sherlock *character);
    BaseItem *get();
    BaseItem *get(ItemType itemType);
};
class WatsonBag : public BaseBag
{
    friend class TestStudyInPink;

private:
    Watson *watson;

public:
    WatsonBag(Watson *character);
    BaseItem *get();
    BaseItem *get(ItemType itemType);
};
class StudyInPinkProgram
{
    friend class TestStudyInPink;
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;
};
class StudyPinkProgram
{
    friend class TestStudyInPink;

private:
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;

public:
    StudyPinkProgram(const string &config_file_path);
    bool isStop() const;

    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose)
    {
        for (int istep = 0; istep < config->num_steps; ++istep)
        {
            for (int i = 0; i < arr_mv_objs->size(); ++i)
            {
                arr_mv_objs->get(i)->move();
                if (isStop())
                {
                    printStep(istep);
                    break;
                }
                if (verbose)
                {
                    printStep(istep);
                }
            }
        }
        printResult();
    }
    ~StudyPinkProgram();
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
