#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <thread>
#include <chrono>

template<typename T>
void retry(T& a) {
	while (!(std::cin >> a))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "digite um numero valido \n";
	}
}

class pessoa {
private:
	std::string nome;
	int idade;
	int id;
	static int Id;

public:
	
	pessoa(const std::string& Nome, int Idade) : nome(Nome), idade(Idade) {
		++Id;
		id = Id;
	}

	static void salvar(const std::vector<pessoa>& pessoas, const std::string& local);
	static std::vector<pessoa> ler(const std::string& local);

	friend std::ostream& operator<<(std::ostream& os, const pessoa& p) {
		os << "Id: " << p.id << " | Nome: " << p.nome << " | Idade: " << p.idade << "\n";
		return os;
	}

};

int pessoa::Id = 0;

void pessoa::salvar(const std::vector<pessoa>& pessoas, const std::string& local){

	std::ofstream save(local);

	if (!save.is_open()) {
		std::cout << "erro ao abrir o arquivo";
		return;
	}

	for (const auto& pessoa : pessoas) {
		save << pessoa.id << " " << pessoa.nome << " " << pessoa.idade << "\n";
	}

	save.close();

}


std::vector<pessoa> pessoa::ler(const std::string& local) {
	std::vector<pessoa> pessoas;
    std::ifstream leitura(local);

    if (!leitura.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return pessoas;
    }

    std::string linha;
    while (std::getline(leitura, linha)) {
        size_t pos = linha.find(" ");
        if (pos != std::string::npos) {
			int id = std::stoi(linha.substr(0, pos));
			size_t nextpos = linha.find(" ", pos + 1);
			
			if (nextpos != std::string::npos) {
				std::string nome = linha.substr(pos + 1, nextpos - pos - 1);
				int idade = std::stoi(linha.substr(nextpos + 1));
				pessoas.emplace_back(nome, idade);
			}
        }
    }

    leitura.close();
    return pessoas;
}

int main() {
	
	std::vector<pessoa> p;
	std::string local = "Pessoas.txt";
	int opcao;
	std::string nome;
	int idade;

	p = pessoa::ler(local);

	do
	{

		std::cout << "\n -----Digite----- \n";
		std::cout << "[1] Para adicionar cadastro \n";
		std::cout << "[2] Para ver todos o cadastro \n";
		std::cout << "[3] Para sair \n";

		retry(opcao);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();

		switch (opcao){

		case 1:{
			std::cout << "Digite o Nome \n";
			std::getline(std::cin, nome);

			std::cout << "Digite a idade \n";
			retry(idade);

			p.emplace_back(nome, idade);
			pessoa::salvar(p, local);
			break;
		}

		case 2: {
			system("cls");

			if (p.empty()) {
				std::cout << "nenhum cadastro encontrado \n";
			}else {
				for (int i = 0; i < p.size(); ++i) {
					std::cout << p[i];
				}
			}
			break;
		}

		case 3: {
			std::cout << "SAINDO...";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		}

		default:
			std::cout << "digite um numero valido \n";
			break;
		}

	} while (opcao != 3);
}