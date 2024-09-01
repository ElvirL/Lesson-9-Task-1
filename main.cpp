/*
������� 1. ���������� ������� ������
��� ����� �������
������ ����� ����������� ���� ������� � ����, ����� �� ��������. ����� ��������� ������ �� ������ ��������, � ����� ���������� ����� 
���������� ������� ������������ �����.
����� � ���� ���� ��������, ������ �� ������� ������������ � ������� ��������� �����, �������� � ��������� ����� ����������. 
�� ������ ������ ���� 3�5 �������� ������� ������. �� ������ ������� ����� ����������� ��� 2-3 ������� �����. ���� ������ ��������� 
�� ������� � �� ������� ������. ����� ������ ����� �� ��������������� � ���� ������.
� ������ ��������� ������������ ��������� � ������ ���� �� ������ �����. �������� ��� � ������� ����������������� �������� ���� 
��������� ����� � ������� ����� ����������� ����� ����� ����������� ����. ���� ���� ������� None � �������� �����, �� ��� ������������ 
� �� ���������� �����.
����� ����� ��������� ����� ������������ ����� �� �����. ��� �������� ����� �������� ����� ����������� ����. ��� ���������� ����� 
����� ������� ����� ���������� ������, ������� ������ � ��� �� ����� ������� �����. ��� � ����� ������� ���������� �������.

������ � ������������
� ��� ������������� ��������, � ��� ������������� ������� � ������� ������ ������� ������������ ���� � ��� �� ����� (�������� Branch) 
� �����, ������� ����� ���������� ������������ �����, � �����, ������������ �������� �����. � ������ ������, � ���� �������, 
������������ ����� ����� ������ �������, �� ���� nullptr.
������� ������ ����� � ������ ����� ����������� � ������� ������������ ������ � ������ Branch, ������� ������� ������ ����� � ����, 
� ����� ��� �� �������� ������.
����� ����� ������������ ��������� ������ � ��������, ��� �������� ��� �������, ��������� �� ������ �����:

Branch\* getTopBranch()
{
//���� ��� ������
if (parent == nullptr) return nullptr;
//���� ��� ������� �����
if (parent->parent == nullptr) return parent;
//���� ��� ��������� �����
return parent->getTopBranch();
}
[]()
*/

#include <iostream>
#include <vector>
#include <ctime>

class Branch{
    Branch* parent = nullptr;
    std::vector<Branch> children;
    std::string name_elf = "None";

public:
    int find_elf(std::string name){
       for (size_t i=0; i< this->children.size(); ++i){
            if (this->children[i].name_elf == name){
                return this->children[i].children.size();
            }

            for (size_t j=0; j<this->children[i].children.size(); ++j){
                if (this->children[i].children[j].name_elf == name){
                    return this->children[i].children.size();
                }
            }  
       }
       return 0;
    }

    void set_parent(Branch* in_parent){
        this->parent = in_parent;
    }

    void add_children(Branch children){
        this->children.push_back(children);
    }

    void set_name(std::string name){
        name_elf = name;
    }

    void print_name(){
        std::cout << name_elf << std::endl;
    }

};

int main(){
    Branch trees[5];

    for (int i=0; i<5; ++i){
        std::srand(time(0));
        int count_big_branches = (std::rand() % 3) + 3;

        for (int j=0; j<count_big_branches; ++j){
            std::cout << "Enter the name of the elf: ";
            std::string elf_name;
            std::cin >> elf_name;
            Branch big_branch;
            big_branch.set_parent(&trees[i]);
            big_branch.set_name(elf_name);

            int count_medium_branch = (std::rand() % 2) + 2;

            for (int k = 0; k<count_medium_branch; ++k){
                std::cout << "Enter the name of the elf: ";
                std::cin >> elf_name;
                Branch medium_branch;
                medium_branch.set_parent(&big_branch);
                medium_branch.set_name(elf_name);
                big_branch.add_children(medium_branch);
            }

            trees[i].add_children(big_branch);
        }
    }

    while (true){
        std::cout << "Enter the name of the elf you are looking for: ";
        std::string elf_name;
        std::cin >> elf_name;

        Branch search_branch;
        for (int i=0; i<5; ++i){
            int cout_neighbour = trees[i].find_elf(elf_name);
            if (cout_neighbour > 0){
                std::cout << "Number of neighbors: " << trees[i].find_elf(elf_name) << std::endl;
                break;
            }
        }
    }
}

