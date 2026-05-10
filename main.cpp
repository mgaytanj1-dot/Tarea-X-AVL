#include <iostream>
#include <algorithm>

using namespace std;

struct Student {
    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Node {

    Student data;

    Node* left;
    Node* right;

    int height;

    Node(Student student) {

        data = student;

        left = nullptr;
        right = nullptr;

        height = 1;
    }
};

class AVLTree {

private:

    Node* root;
    int totalNodes;

    int getHeight(Node* node) {

        if (node == nullptr)
            return 0;

        return node->height;
    }

    int getBalance(Node* node) {

        if (node == nullptr)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left),
                        getHeight(y->right)) + 1;

        x->height = max(getHeight(x->left),
                        getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left),
                        getHeight(x->right)) + 1;

        y->height = max(getHeight(y->left),
                        getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, Student student) {

        if (node == nullptr)
            return new Node(student);

        if (student.skill_score < node->data.skill_score)
            node->left = insert(node->left, student);

        else if (student.skill_score > node->data.skill_score)
            node->right = insert(node->right, student);

        else
            return node;

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 &&
            student.skill_score < node->left->data.skill_score)
            return rightRotate(node);

        if (balance < -1 &&
            student.skill_score > node->right->data.skill_score)
            return leftRotate(node);

        if (balance > 1 &&
            student.skill_score > node->left->data.skill_score) {

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 &&
            student.skill_score < node->right->data.skill_score) {

            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node* node, int& position) {

        if (node != nullptr) {

            inOrder(node->right, position);

            cout << position << ". "
                 << node->data.full_name
                 << " - Score: "
                 << node->data.skill_score
                 << endl;

            position++;

            inOrder(node->left, position);
        }
    }

    Node* search(Node* node, int score) {

        if (node == nullptr ||
            node->data.skill_score == score)
            return node;

        if (score < node->data.skill_score)
            return search(node->left, score);

        return search(node->right, score);
    }

public:

    AVLTree() {

        root = nullptr;
        totalNodes = 0;
    }

    void insertStudent(Student student) {

        root = insert(root, student);
        totalNodes++;
    }

    void showRanking() {

        if (root == nullptr) {

            cout << "\nNo hay estudiantes registrados.\n";
            return;
        }

        int position = 1;

        cout << "\n========== RANKING ACADEMICO ==========\n";

        inOrder(root, position);
    }

    void searchBySkillScore(int score) {

        Node* result = search(root, score);

        if (result == nullptr) {

            cout << "\nEstudiante no encontrado.\n";
        }
        else {

            cout << "\n========== ESTUDIANTE ENCONTRADO ==========\n";

            cout << "ID: "
                 << result->data.student_id << endl;

            cout << "Nombre: "
                 << result->data.full_name << endl;

            cout << "Carrera: "
                 << result->data.career << endl;

            cout << "Semestre: "
                 << result->data.semester << endl;

            cout << "GPA: "
                 << result->data.gpa << endl;

            cout << "Skill Score: "
                 << result->data.skill_score << endl;
        }
    }

    void showStatistics() {

        cout << "\n========== ESTADISTICAS AVL ==========\n";

        cout << "Altura actual del arbol: "
             << getHeight(root) << endl;

        cout << "Factor de balance de la raiz: "
             << getBalance(root) << endl;

        cout << "Cantidad de nodos insertados: "
             << totalNodes << endl;
    }
};

int main() {

    AVLTree tree;

    int option;

    do {

        cout << "\n=====================================\n";
        cout << "     SISTEMA DE RANKING AVL\n";
        cout << "=====================================\n";

        cout << "1. Insertar estudiante\n";
        cout << "2. Mostrar ranking academico\n";
        cout << "3. Buscar por skill_score\n";
        cout << "4. Mostrar estadisticas AVL\n";
        cout << "5. Salir\n";

        cout << "\nSeleccione una opcion: ";
        cin >> option;

        switch(option) {

        case 1: {

            Student s;

            cout << "\n========== INGRESAR ESTUDIANTE ==========\n";

            cout << "ID del estudiante: ";
            cin >> s.student_id;

            cin.ignore();

            cout << "Nombre completo: ";
            getline(cin, s.full_name);

            cout << "Carrera: ";
            getline(cin, s.career);

            cout << "Semestre: ";
            cin >> s.semester;

            cout << "GPA: ";
            cin >> s.gpa;

            cout << "Skill Score: ";
            cin >> s.skill_score;

            tree.insertStudent(s);

            cout << "\nEstudiante insertado correctamente.\n";

            break;
        }

        case 2:

            tree.showRanking();
            break;

        case 3: {

            int score;

            cout << "\nIngrese el skill_score a buscar: ";
            cin >> score;

            tree.searchBySkillScore(score);

            break;
        }

        case 4:

            tree.showStatistics();
            break;

        case 5:

            cout << "\nSaliendo del programa...\n";
            break;

        default:

            cout << "\nOpcion invalida.\n";
        }

    } while(option != 5);

    return 0;
}
