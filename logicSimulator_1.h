#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

typedef enum nodeType {INPUT, OUTPUT, NOT, AND, NAND, OR, NOR, XOR} nodeType; // Type of node
typedef enum nodeState {low, high, unknown} nodeState; // State of node

class Wire; // Forward Declaration of Class Wire

class Node {
public:
    std::string name;
    nodeType type;
    nodeState state;
    std::list <Wire*> inputWiresList; // list containing the references to wires which are input to this node
    std::list <Wire*> outputWiresList; // list containing the references to wires which are output to this node
    
    void printNodeInfo();
    
    void addInputWire (Wire* inputWireInstance);
    
    void addOutputWire (Wire* outputWireInstance);
    
    void showInputWires ();

    void showOutputWires ();
    
    void evaluate ();
    
    Node(std::string nameValue, nodeType typeValue, nodeState stateValue);
    
    ~Node() {}
    
};

class Wire {
public:
    std::string label;
    Node* drivingNode;
    Node* drivenNode;
    
    void printWireInfo();
    
    Wire(std::string labelValue, Node* driving_node, Node* driven_node);
    
    ~Wire() {}
};

class Netlist {
public:
    std::vector<Node*> pointerToNodes;
    
    int addNodes(Node* node);
    
    int showAllInputNodes();
    
    int showAllOutputNodes();
    
    int showAllNodes();
    
    int searchNode(string nameOfTheNode);
  
    ~Netlist() {}
};


