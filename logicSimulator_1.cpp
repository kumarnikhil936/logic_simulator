#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<fstream>
#include<regex>
#include <boost/tokenizer.hpp>
#include "logicSimulator_1.h"

Wire::Wire(std::string labelValue, Node* driving_node, Node* driven_node) {
    label        = labelValue;
    drivingNode  = driving_node;
    drivenNode   = driven_node;
}

void Wire::printWireInfo() {
    std::cout<<"The wire label is : " << label << endl;
    std::cout<<"The driving node is : "<< drivingNode->name << endl;
    std::cout<<"The driven node is : "<< drivenNode->name << endl << endl;
}

Node::Node(std::string nameValue, nodeType typeValue, nodeState stateValue) {
    name=nameValue;
    type=typeValue;
    state=stateValue;
}

void Node::printNodeInfo() {
    std::cout<<"The name of the instance is " << name << endl;
    std::cout<<"The state of the instance is " << state << endl;
    std::cout<<"The node is of type: " << type << endl << endl;
}

void Node::addInputWire (Wire* inputWireInstance) {
    inputWiresList.push_back(inputWireInstance);
}

void Node::addOutputWire (Wire* outputWireInstance) {
    outputWiresList.push_back(outputWireInstance);
}

void Node::showInputWires() {
    for (auto i : inputWiresList)
        std::cout<< i->label <<" : is an input wire from the node : " << name << endl;
}

void Node::showOutputWires() {
    for (auto o : outputWiresList)
        std::cout<< o->label <<" : is an output wire to the node : " << name << endl;
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

int Netlist::addNodes(Node* node) {
    pointerToNodes.push_back(node);
    std::cout << "Added to the netlist node : " << node->name << std::endl;
    return 0;
}

int Netlist::showAllInputNodes(){
    size_t vectorSize = pointerToNodes.size();
    size_t numInputNodes = 0;
    std::cout << "\nDisplaying the list of Input nodes in the circuit\n";
    for (int i = 0; i < vectorSize; i++) {
        if (pointerToNodes[i]->type == INPUT) {
            cout << pointerToNodes[i]->name << endl;
            numInputNodes++;
        }
    }
    std::cout << "The total number of Input nodes are : " << numInputNodes << "\n\n";
    return 0;
}

int Netlist::showAllOutputNodes(){
    size_t vectorSize = pointerToNodes.size();
    size_t numOutputNodes = 0;
    std::cout << "\nDisplaying the list of Output nodes in the circuit\n";
    for (int i = 0; i < vectorSize; i++) {
        if (pointerToNodes[i]->type == OUTPUT) {
            cout << pointerToNodes[i]->name << endl;
            numOutputNodes++;
        }
    }
    std::cout << "The total number of Output nodes are : " << numOutputNodes << "\n\n";
    return 0;
}

int Netlist::showAllNodes(){
    size_t vectorSize = pointerToNodes.size();
    std::cout << "\nDisplaying all the nodes in the circuit\n";
    for (int i = 0; i < vectorSize; i++) {
        cout << "Node " << pointerToNodes[i]->name << " of type " << pointerToNodes[i]->type << std::endl;
    }
    return 0;
}

int Netlist::searchNode(string nameOfTheNode) {
    size_t vectorSize = pointerToNodes.size();
    bool found = 0;
    std::cout << "Looking for node - " << nameOfTheNode << " in the circuit netlist \n";
    for (int i = 0; i < vectorSize; i++) {
        if (pointerToNodes[i]->name == nameOfTheNode)
            found = 1;
    }
    if (found)
        std::cout << "Found the node - " << nameOfTheNode << " \n\n";
    else
        std::cout << "Could not find the node - " << nameOfTheNode << " \n\n";
    
    return 0;
}

bool is_number(const std::string& s)
{
    return( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

int main ()
{
    /*Netlist circuit1;
    
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
    
    circuit1.addNodes(&a);
    circuit1.addNodes(&b);
    circuit1.addNodes(&cin);
    circuit1.addNodes(&d);
    circuit1.addNodes(&e);
    circuit1.addNodes(&f);
    circuit1.addNodes(&g);
    circuit1.addNodes(&h);
    circuit1.addNodes(&s);
    circuit1.addNodes(&cout);
    
    circuit1.showAllInputNodes();
    circuit1.showAllOutputNodes();
    
    circuit1.searchNode("cout");
    
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
    
    std::cout << "Before Simulation: \n";*/
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
    
    /*a.addOutputWire(&w1);
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
    */
    
    Netlist c17_bench;

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep("() =,");

    ifstream inFile ("/Users/nikhilkumarjha/Google Drive/UPB Study Material/Matthias Project/c17.bench");
    if (!inFile) cerr << "Can't open input file!";

    char oneline[256];
    std::vector<std::string> lines;
    
    std::vector<Node> nodeObjects;
    std::vector<string> wireNames;

    
    while (inFile)
    {
        inFile.getline(oneline, 256);
        if(inFile.good())    // If a line was successfully read
        {
            if(strlen(oneline) == 0)  // Skip any blank lines
                continue;
            else if(oneline[0] == '#')  // Skip any comment lines
                continue;
            //else done = true;    // Got a valid data line so return with this line
        }
        else // No valid line read, meaning we reached the end of file
        {
            strcpy(oneline, ""); // Copy empty string into line as sentinal value
        }
        //std::cout << oneline << endl;
        lines.push_back(oneline);
    } // Read the complete file and push every line in a vector "lines"
    
    
    // Read every line from the vector and tokenize it
    for (std::vector<string>::iterator itr = lines.begin() ; itr != lines.end(); ++itr) {
        //std::cout << ' ' << *itr << std::endl;
        
        string str;
        string nodetype;
        string wirename;
        int i = 0;

        str = *itr;

        tokenizer tokens(str, sep);
        
        Node * a[100];
        
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
            //std::cout << "<" << *tok_iter << "> \n";
            i++;
            
            if (is_number(*tok_iter)) {
                wirename = *tok_iter;
                wireNames.push_back(wirename);
            }
            else if (*tok_iter == "INPUT" | *tok_iter == "OUTPUT" )
            {
                nodetype = *tok_iter;
                continue;
            }
            else if ( *tok_iter == "AND" | *tok_iter == "NAND" | *tok_iter == "NOT" | *tok_iter == "NOR" |*tok_iter == "OR" | *tok_iter == "XOR"  ) {
                nodetype = *tok_iter;
            }
            
            //std::regex inputNode ("(INPUT)(.*)");
            //if (std::regex_match (nodetype,inputNode)) {
            
            if (nodetype == "INPUT") {
                a[i] = new Node(*tok_iter, INPUT, high);
                std::cout << "Created a node " << *tok_iter << " of type INPUT. \n";
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "OUTPUT") {
                a[i] = new Node(*tok_iter, OUTPUT, high);
                std::cout << "Created a node " << *tok_iter << " of type OUTPUT. \n" ;
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "NAND") {
                a[i] = new Node(wirename, NAND, high);
                std::cout << "Created a node " << wirename << " of type NAND. \n";
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "NOR") {
                a[i] = new Node(wirename, NOR, high);
                std::cout << "Created a node " << wirename << " of type NOR. \n" ;
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            else if (nodetype == "OR") {
                a[i] = new Node(wirename, OR, high);
                std::cout << "Created a node " << wirename << " of type OR. \n" ;
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "NOT") {
                a[i] = new Node(wirename, NOT, high);
                std::cout << "Created a node " << wirename << " of type NOT. \n";
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "AND") {
                a[i] = new Node(wirename, AND, high);
                std::cout << "Created a node " << wirename << " of type AND. \n" ;
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
            else if (nodetype == "XOR") {
                a[i] = new Node(wirename, XOR, high);
                std::cout << "Created a node " << wirename << " of type XOR. \n" ;
                c17_bench.addNodes(a[i]);
                nodetype = "NULL";
            }
            
          
            std::cout << "\n";
            
        }
    }

    //c17_bench.searchNode("7");
    
    c17_bench.showAllNodes();
    
    // c17_bench.showAllInputNodes();
    // c17_bench.showAllOutputNodes();
    
    /*size_t wireNameVectorSize = wireNames.size();
    std::cout << "\nDisplaying the list of wires in the circuit\n";
    for (int i = 0; i < wireNameVectorSize; i++) {
        cout << wireNames[i] << std::endl;
        }
    */
    inFile.close();
    
    return 0;
}


