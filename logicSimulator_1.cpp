#include<iostream>
#include<string>
#include<list>
using namespace std;

typedef enum nodeType {INPUT, OUTPUT, NOT, AND, NAND, OR, NOR, XOR} nodeType; // Type of node
typedef enum nodeState {low, high, unknown} nodeState; // State of node

class Wire; // Forward Declaration of Class Wire

class Node {
public:
    std::string name;
    nodeType type;
    std::list <Wire*> inputWiresList; // list containing the references to wires which are input to this node
    std::list <Wire*> outputWiresList; // list containing the references to wires which are output to this node
    nodeState state;
    
    void printNodeInfo() {
        std::cout<<"The name of the instance is " << name << endl;
        std::cout<<"The state of the instance is " << state << endl;
        std::cout<<"The node is of type: " << type << endl << endl;
    }
    
    void addInputWire (Wire* inputWireInstance) {
        inputWiresList.push_back(inputWireInstance);
    }
    
    void addOutputWire (Wire* outputWireInstance) {
        outputWiresList.push_back(outputWireInstance);
    }
    
    void showInputWires ();

    void showOutputWires ();
    
    void evaluate ();
    
    Node(std::string nameValue, nodeType typeValue, nodeState stateValue) {
        name=nameValue;
        type=typeValue;
        state=stateValue;
    }
    // ~Node();
    
};

class Wire {
public:
    std::string label;
    Node* drivingNode;
    Node* drivenNode;
    
    void printWireInfo() {
        std::cout<<"The wire label is : " << label << endl;
        std::cout<<"The driving node is : "<< drivingNode->name << endl;
        std::cout<<"The driven node is : "<< drivenNode->name << endl << endl;
    }
    
    Wire(std::string labelValue, Node* driving_node, Node* driven_node) {
        label        = labelValue;
        drivingNode  = driving_node;
        drivenNode   = driven_node;
    }
    
    ~Wire() {}
};

void Node::showInputWires() {
    for (auto i : inputWiresList)
        std::cout<< i->label <<" : is an input wire from the node : " << name << endl;
    /*for (list<int>::iterator i = inputWiresList.begin(); i != lst.end(); ++i)
     cout << *i << endl;*/
}

void Node::showOutputWires() {
    for (auto o : outputWiresList)
        std::cout<< o->label <<" : is an output wire to the node : " << name << endl;
    /*for (list<int>::iterator i = outputWiresList.begin(); i != lst.end(); ++i)
     cout << *i << endl;*/
}

void Node::evaluate(){
    switch (type) {
        case 0: // INPUT
            break;
        case 1: // OUTPUT
            for (auto i : inputWiresList)
                state = nodeState((i->drivingNode->state));
            break;
        case 2: // NOT
            for (auto i : inputWiresList)
                state = nodeState(~(i->drivingNode->state));
            break;
        case 3: // AND
            nodeState temp3;
            temp3 = inputWiresList.front()->drivingNode->state;
            for (auto i : inputWiresList) {
                temp3 = nodeState(temp3 & nodeState(i->drivingNode->state));
            }
            state = temp3;
            break;
        case 4: // NAND
            nodeState temp1;
            temp1 = inputWiresList.front()->drivingNode->state;
            for (auto i : inputWiresList) {
                temp1 = nodeState(temp1 & nodeState(i->drivingNode->state));
            }
            state = nodeState(~(temp1));
            break;
        case 5: // OR
            nodeState temp4;
            temp4 = inputWiresList.front()->drivingNode->state;
            for (auto i : inputWiresList) {
                temp4 = nodeState(temp4 | nodeState(i->drivingNode->state));
            }
            state = temp4;
            break;
        case 6: // NOR
            nodeState temp2;
            temp2 = inputWiresList.front()->drivingNode->state;
            for (auto i : inputWiresList) {
                temp2 = nodeState(temp2 | nodeState(i->drivingNode->state));
            }
            state = nodeState(~(temp2));
            break;
        case 7: // XOR
            int fanIn;
            fanIn=0;
            nodeState temp5;
            for (auto i : inputWiresList) {
                if (fanIn == 0)
                    temp5 = nodeState(i->drivingNode->state);
                else
                    temp5 = nodeState(temp5 ^ nodeState(i->drivingNode->state));
                fanIn += 1;
            }
            state = temp5;
            break;
        default:
            break;
    }
}

int main ()
{
    Node a("a", INPUT, high);
    Node b("b", INPUT, low);
    Node cin("cin", INPUT, low);
    Node d("d", XOR, low);
    Node e("e", XOR, low);
    Node f("f", AND, low);
    Node g("g", AND, low);
    Node h("h", OR, low);
    Node s("s", OUTPUT, low);
    Node cout("cout", OUTPUT, low);

    Wire w1("w1", &a, &d);
    Wire w2("w2", &b, &d);
    Wire w3("w3", &d, &e);
    Wire w4("w4", &cin, &e);
    Wire w5("w5", &d, &f);
    Wire w6("w6", &cin, &f);
    Wire w7("w7", &a, &g);
    Wire w8("w8", &b, &g);
    Wire w9("w9", &e, &s);
    Wire w10("w10", &f, &h);
    Wire w11("w11", &g, &h);
    Wire w12("w12", &h, &cout);
    
    std::cout << "Before Simulation: \n";
    /*a.printNodeInfo();
    b.printNodeInfo();
    cin.printNodeInfo();
    d.printNodeInfo();
    e.printNodeInfo();
    f.printNodeInfo();
    g.printNodeInfo();
    h.printNodeInfo();
    s.printNodeInfo();
    cout.printNodeInfo();*/
    
    /*w1.printWireInfo();
    w2.printWireInfo();
    w3.printWireInfo();
    w4.printWireInfo();
    w5.printWireInfo();
    w6.printWireInfo();
    w7.printWireInfo();
    w8.printWireInfo();
    w9.printWireInfo();
    w10.printWireInfo();
    w11.printWireInfo();
    w12.printWireInfo();*/
    
    a.addOutputWire(&w1);
    a.addOutputWire(&w7);
    
    b.addOutputWire(&w2);
    b.addOutputWire(&w8);
    
    cin.addOutputWire(&w4);
    cin.addOutputWire(&w6);
    
    d.addInputWire(&w1);
    d.addInputWire(&w2);
    d.addOutputWire(&w3);
    d.addOutputWire(&w5);
    
    e.addInputWire(&w3);
    e.addInputWire(&w4);
    e.addOutputWire(&w9);
    
    f.addInputWire(&w5);
    f.addInputWire(&w6);
    f.addOutputWire(&w10);
    
    g.addInputWire(&w7);
    g.addInputWire(&w8);
    g.addOutputWire(&w11);
    
    h.addInputWire(&w10);
    h.addInputWire(&w11);
    h.addOutputWire(&w12);
    
    s.addInputWire(&w9);
    
    cout.addInputWire(&w12);
    
    // Calling evaluate function on all the nodes
    a.evaluate();
    b.evaluate();
    cin.evaluate();
    d.evaluate();
    e.evaluate();
    f.evaluate();
    g.evaluate();
    h.evaluate();
    s.evaluate();
    cout.evaluate();
    
    std::cout << "After Simulation: \n";
    a.printNodeInfo();
    b.printNodeInfo();
    cin.printNodeInfo();
    d.printNodeInfo();
    e.printNodeInfo();
    f.printNodeInfo();
    g.printNodeInfo();
    h.printNodeInfo();
    s.printNodeInfo();
    cout.printNodeInfo();
    
    return 0;
}

