// Declarações do programa
#include <iostream>
#include <Windows.h>
using namespace std;

// definições
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
#define QTDE_CLIENTES						2000
#define CAMINHO_CADASTRO					"..\\Cadastro.cad"
#define ATIVO								'A'
#define INATIVO								'I'
#define TAM_NOME							40

// opções do menu do operador
#define INCLUIR_CLIENTE						'I'
#define EXCLUIR_CLIENTE						'E'
#define SACAR_CHEQUE						'C'
#define FAZER_DEPOSITO						'D'
#define MOSTRAR_CLIENTE						'M'
#define SAIR_DO_PROGRAMA					'S'

//
// struct de um cliente
//
typedef struct tagCLIENTE
{
	int nCodigo;																	// 1, 2, 3, .........QTDE_CLIENTES
	char cAtivo,																	// 'A' - ativo e 'I' - inativo
		CnomeCliente[TAM_NOME + 1];													// nome do cliente
	double dSaldo,																	// saldo do cliente
		dVlrTotalCheques,															// total de cheques
		dVlrTotalDepositos;															// total de depósitos
} CLIENTE;

// Protótipos das funções
bool PedirCodigoCliente(int *ptrCodigo, char *ptrTransacao);
bool LerPosional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro);
bool GravarPosicional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro);