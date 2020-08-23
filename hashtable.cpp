#include <string>
#include <fstream>
#include <iostream>
#include <vector>
const int MAX_SIZE = 20;

struct var
{
    std::string var_name; //The var_name is the key. 
    int value;
    int scope;
    var* next;
    var(std::string expression, int data, int scope_item) {
        var_name = expression;
        value = data;
        scope = scope_item;
        next = nullptr;
    } //Constructor
};

class HashTable {

public:
    HashTable();
    //Default Constructor: Initializes all pointers to null pointers.

    int hash_Function(std::string key);
    //The hash function. Performs operations on the variable name which is the key to return a hash value.

    void insert_Item(var item);
    //Inserts a struct of type var into the hash table.

    var hash_Search(std::string var_name);
    //Searches for string var_name in the hash table.

    void hash_Print(std::string var_name, int scope);

    void modify_value(std::string var_name, int operation, int operand);
    // 1 = addition, 0 = substraction

private:
    var* hash_Table[MAX_SIZE];

};

int main() {

    std::ifstream myfile;
    myfile.open("input.txt", std::ios::in);
    std::vector<std::string> data;
    HashTable* ht = new HashTable();
    if(myfile.is_open()) {
        int scope = 0;
      while (!myfile.eof()){
          std::string line;
          getline(myfile,line);
          int i = 0;
          while(line.at(i) == ' ')
            i++;
        if (line.substr(i,3).compare("COM") == 0)
            std::cout << "";

        else if (line.substr(i,5).compare("START") == 0) {
            scope++;
        }
        else if (line.substr(i,3).compare("VAR") == 0) {
            std::string tobeParsed = line.substr(4+i,line.length());
            int j = 0;
            while (tobeParsed.at(j) != ' ')
            j++;
            std::string varName = tobeParsed.substr(0,j);
            std::string value = tobeParsed.substr(j+3,tobeParsed.length());
            int value_int = stoi(value);
            var* temp = new var(varName, value_int, scope);
            ht->insert_Item(*temp);
        }
        else if (line.substr(i,5).compare("PRINT") == 0) {
            std::string thisIs = line.substr(i,5);
            std::string toBePrinted = line.substr(7,line.length());
            int length = toBePrinted.length();
            int j = 0;
            while(toBePrinted.at(j) == ' ')
                j++;
          
             std:: string tobeSent = toBePrinted.substr(j,line.length());
            ht->hash_Print(tobeSent, scope);

        }
        else if (line.substr(i,6).compare("FINISH") == 0) {
            scope--;
        }
        else {
           int j =0;
           while (line.at(j+i) != ' ')
           j++;
           std::string var_name = line.substr(i,j);
           char x = line.at(j+3);
           if (line.at(j+3) == '=') {
               std::string value = line.substr(j+5,line.length());
            ht->modify_value(var_name,3, stoi(value));
           }
           std::string operation = line.substr(j+2,j+4);
           if (operation.compare("++") == 0) {
              ht->modify_value(var_name,1, 0);
           }
            else if (operation.compare("--") == 0)
            ht->modify_value(var_name,0, 0);

           }



        }
      }
        myfile.close();
    }

  

HashTable::HashTable() {
    for (int i = 0; i < 20; i++)
        hash_Table[i] = nullptr;
}


int HashTable::hash_Function(std::string key) {
    int length = key.length();
    int value;
    for (int i = 0; i < length; i++)
        value += int(key.at(i)) * (i+1);
    return value % MAX_SIZE;
}

void HashTable::insert_Item(var Node) {
    var* temp = new var(Node.var_name,Node.value,Node.scope);
    int hash_value = hash_Function(Node.var_name);
    if (hash_Table[hash_value] == nullptr) {
        hash_Table[hash_value] = temp;
    }
    else {
        var* tempo = hash_Table[hash_value];
        while (tempo->next != NULL) {
            tempo = tempo->next;
        }
        (*tempo).next = temp;
    }
}

var HashTable::hash_Search(std::string var_name) {
    int key = hash_Function(var_name);
    var* temp = hash_Table[key];
    if  (temp == nullptr)
        return var("",-999,-1);
    while (temp->var_name.compare(var_name) != 0)
        temp = temp->next;
    return *temp;
}

void HashTable::hash_Print(std::string var_name, int scope) {

    bool flag_2 = false;

    bool flag = false;
    
    int i = 0;
    int length_o = var_name.length();
    for ( i = 0; i<length_o;i++) 
        if (var_name.at(i) == ' ') {
            std::string var_true_name = var_name.substr(0,i);
            var temp = hash_Search(var_true_name);
            flag = true;
            char operation = var_name.at(i+1);
            std::string operand =var_name.substr(i+3,var_name.length());
            int operand_int = stoi(operand);
            if (temp.scope <= scope) {
                if (operation == '+')
                    std::cout << var_name << " IS " << temp.value+operand_int << "\n";
                 if (operation == '*')
                    std::cout << var_name << " IS " << temp.value*operand_int <<"\n";
                 if (operation == '/')
                    std::cout << var_name << " IS " << temp.value/operand_int <<"\n";
                 if (operation == '-')
                    std::cout << var_name << " IS"  << temp.value-operand_int <<"\n";
                break;
            }
            else std::cout << var_name <<" IS UNDEFINED.\n";
    }

    var temp = hash_Search(var_name);
    if (temp.scope == -1 && flag==false) {
         std::cout << var_name << " IS UNDEFINED.\n";
         flag_2 = true;
    }
    
    if (flag == false && flag_2 == false) {
    if (temp.scope <=scope)
    std::cout << var_name   <<  " IS " << temp.value << "\n";
    else
    std::cout << var_name << " IS UNDEFINED.\n";
    }
}

void HashTable::modify_value(std::string var_name, int operation, int operand) {
    var* temp;
   int hashed_key = hash_Function(var_name);
   temp = hash_Table[hashed_key];
   while (temp->var_name.compare(var_name) != 0)
        temp = temp->next;
    if (operation == 1)
    (temp->value)++;
    else if (operation==0)
    (temp->value)--;
    else if (operation ==3)
    (temp->value) = operand;
}