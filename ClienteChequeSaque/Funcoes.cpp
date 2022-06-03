// Fun��es do programa de cadastramento de clientes
#include "Header.h"

// Fun��o que pede um c�digo de cliente v�lido
// Se for digitado 0 (zero) indica que o operador quer cancelar a opera��o ou transa��o
//	que est� sendo executada
//	Par�metros:
//		Entrada: int *ptrCodigo - ponteiro de uma inteira do chamador da fun��o
//									que receber� um c�digo v�lido
//				 char *ptrTransacao - string que indica transa��o sendo executada
//		Retorno: bool - true - tem um c�digo v�lido de cliente
//						false - indica cque o operador cancelou a transa��o
bool PedirCodigoCliente(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "C�digo Cliente (1 a " << QTDE_CLIENTES << "): ";
		cin >> *ptrCodigo;														// recebe o c�digo

		if(*ptrCodigo == 0)														// cancelou?
			return false;														// indica que cancelou

	} while( *ptrCodigo < 1 || *ptrCodigo > QTDE_CLIENTES);
	return true;																// indica que tem um c�digo v�lido

}

// Fun��o que l� posicional um cliente
// Par�metros:
//		Entrada: int nCodigo - c�digo do cliente a ser acessado diretamente
//				 CLIENTE *ptrBuffer - endere�o do buffer de leitura
//				 FILE *fdCadastro - file descriptor do cadastro
//		Retorno: bool - true - tudo ok
//						false - houve erro fseek ou fread_s
bool LerPosional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro)
{
	if(fseek(fdCadastro, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0)			// erro?
		return false;

	if(fread_s(ptrBuffer, sizeof(CLIENTE), sizeof(CLIENTE), 1, fdCadastro) == 0)	// erro?
		return false;
	return true;																	// indica tudo OK													

}

// Fun��o que grava posicional um cliente
// Par�metros:
//		Entrada: int nCodigo - c�digo do cliente a ser acessado diretamente
//				 CLIENTE *ptrBuffer - endere�o do buffer de grava��o
//				 FILE *fdCadastro - file descriptor do cadastro
//		Retorno: bool - true - tudo ok
//						false - houve erro fseek ou fwrite
bool GravarPosicional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro)
{
	if(fseek(fdCadastro, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0)			// erro?
		return false;																// indica erro

	if(fwrite(ptrBuffer, sizeof(CLIENTE), 1, fdCadastro) == 0)						// erro?
		return false;																// indica erro
	return true;																	// indica tudo OK

}