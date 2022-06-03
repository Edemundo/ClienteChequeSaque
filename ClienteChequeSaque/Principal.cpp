// Programa de atualização de um arquivo de clientes
// FATEC-MC - JCB -10/05/2017 - Versão 0.0

#include"Header.h"

//
// entry point da main
//
void main(void)
{
	int i,																		// indexador e contador
		nCodigo;																// recebe o codigo do cliente
	char cOpcao,																// opção do operador
		cConfirmar,																// para confirmar os ifs do programa
		cWork[200];																// para uso do sprintf_s
	CLIENTE stCliente;															// para conter os dados de um cliente
	FILE *fdCadastro;															// file descriptor do cadastro de clientes
	SYSTEMTIME stTime;															// para receber data e hora
	double dSaqueDeposito;														// para quando o cliente for sacar ou depositar

	PAIS_BRASIL;																// acentuação brasileira

	// vamos abrir o arquivo em modo leitura/gravação - precisa existir
	if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0)						// erro de abertura?
	{
		// é aprimeira vez que o programa vai ser executado
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0)					// erro de abertura?
		{	
			// foi tentado abrir em modo gravação/leitura - se existir zera o arquivo
			cout << "Erro de abertura do arquivo: " << CAMINHO_CADASTRO << endl;
			PAUSA;
			return;																// volta ao S.O.
		}

		for(i = 0; i < QTDE_CLIENTES; i++)										// loop de "formatação" do cadastro
		{
			stCliente.cAtivo = INATIVO;											// cliente inativo
			stCliente.nCodigo = i + 1;											// 1, 2, 3,.....QTDE_CLIENTES
			if(fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0)			// erro de gravação?
			{
				// erro de gravação
				fclose(fdCadastro);												// fechar o arquivo
				cout << "Erro de gravação!" << endl;
				PAUSA;
				return;															// volta ao S.O.

			} // end if

		} // for i

	} // não existe

	//
	// loop infinito do programa
	//
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);													// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Sistema de Cadastramento de Clientes %02d/%02d/%04d %02d:%02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << cWork << endl;

		cout << INCLUIR_CLIENTE << " - Incluir novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << SACAR_CHEQUE << " - Sacar Cheque"<< endl;
		cout << FAZER_DEPOSITO << " - Depositar em dinheiro" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;															// opção do operador
		cOpcao = toupper(cOpcao);												// converte para  maiúscula

		switch(cOpcao)															// avalia a opção escolhida
		{
			case INCLUIR_CLIENTE:
				if(!PedirCodigoCliente(&nCodigo, "Incluir Cliente"))			// cancelou a transação?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stCliente, fdCadastro))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stCliente.cAtivo == ATIVO)									// cliente ativo?
				{
					cout << "Cliente: " << stCliente.nCodigo << " Nome: "
						<< stCliente.CnomeCliente << endl
					<< "Cliente Ativo!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				// cliente inativo
				cin.ignore(1, EOF);												// ignora a tecla Enter anterior
				cout << "Nome: ";
				cin.getline(stCliente.CnomeCliente, TAM_NOME, '\n');
				cout << "Saldo:" ;
				cin >> stCliente.dSaldo;
				stCliente.cAtivo = ATIVO;										// cliente ativo
				stCliente.dVlrTotalCheques = 0;
				stCliente.dVlrTotalDepositos = 0;							// zera os totais

				// vamos gravar
				if(!GravarPosicional(nCodigo, &stCliente, fdCadastro))			// erro?
				{

					cout << "Erro de Gravação!" << endl;
					PAUSA;
				}

				break;															// volta ao menu
			
			case EXCLUIR_CLIENTE:
				if(!PedirCodigoCliente(&nCodigo, "Excluir Cliente"))			// cancelou a transação?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stCliente, fdCadastro))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stCliente.cAtivo == INATIVO)									// cliente inativo?
				{
					cout << "Código inválido, esse cliente não existe!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				// cliente ativo
				cout <<"Código: " << stCliente.nCodigo << " Nome: " << stCliente.CnomeCliente << endl
					<< "Tem certeza que deseja excluir o cliente?" << endl 
					<< "Digite S(Sim) para exluir ou qualquer outra tecla para voltar ao menu: ";
				cin >> cConfirmar;

				if(cConfirmar == 'S' || cConfirmar == 's' )						// quer realmente excluir o cliente?
					stCliente.cAtivo = INATIVO;

				// vamos gravar
				if(!GravarPosicional(nCodigo, &stCliente, fdCadastro))			// erro?
				{
					cout << "Erro de Gravação!" << endl;
					PAUSA;
				}

				break;															// volta ao menu

			case SACAR_CHEQUE:
				if(!PedirCodigoCliente(&nCodigo, "Sacar Cheque"))			// cancelou a transação?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stCliente, fdCadastro))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stCliente.cAtivo == INATIVO)									// cliente inativo?
				{
					cout << "Código inválido, esse cliente não existe!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				// cliente ativo
				cout <<"Código: " << stCliente.nCodigo << " Nome: " << stCliente.CnomeCliente << " Saldo: " << stCliente.dSaldo << endl;

				do
				{
					cout << "Digite o valor que deseja sacar: ";
					cin >> dSaqueDeposito;
					if(dSaqueDeposito > stCliente.dSaldo)
					{	
						cout << "Saldo Indisponível, deseja cancelar a operação?" << endl 
							<< "Digite S(Sim) para cancelar ou qualquer outra tecla para tentar novamente: ";
						cin >> cConfirmar;
						if(cConfirmar == 's' || cConfirmar == 'S')
						{
							cout << " Operação Cancelada!" << endl;
							PAUSA;
							break;
						}	
					}
				} while (dSaqueDeposito > stCliente.dSaldo);

				stCliente.dVlrTotalCheques += dSaqueDeposito;
				stCliente.dSaldo = stCliente.dSaldo - dSaqueDeposito;

				cout << "Saque realizado com sucesso!" << endl;
				
				// vamos gravar
				if(!GravarPosicional(nCodigo, &stCliente, fdCadastro))			// erro?
				{
					cout << "Erro de Gravação!" << endl;
					PAUSA;
				}

				break;															// volta ao menu

			case FAZER_DEPOSITO:
				if(!PedirCodigoCliente(&nCodigo, "Fazer Deposito"))				// cancelou a transação?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stCliente, fdCadastro))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stCliente.cAtivo == INATIVO)									// cliente inativo?
				{
					cout << "Código inválido, esse cliente não existe!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				// cliente ativo
				cout <<"Código: " << stCliente.nCodigo << " Nome: " << stCliente.CnomeCliente << " Saldo: " << stCliente.dSaldo << endl
					<< "Digite quanto deseja depositar: ";
				cin >> dSaqueDeposito;

				stCliente.dSaldo += dSaqueDeposito;
				stCliente.dVlrTotalDepositos += dSaqueDeposito;
				
				cout << "Deposito realizado com sucesso!" << endl;

				// vamos gravar
				if(!GravarPosicional(nCodigo, &stCliente, fdCadastro))			// erro?
				{
					cout << "Erro de Gravação!" << endl;
					PAUSA;
				}

				break;															// volta ao menu

			case MOSTRAR_CLIENTE:
				if(!PedirCodigoCliente(&nCodigo, "Mostrar Cliente"))			// cancelou a transação?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stCliente, fdCadastro))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stCliente.cAtivo == INATIVO)									// cliente inativo?
				{
					cout << "Código inválido, esse cliente não existe!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				sprintf_s(cWork, sizeof cWork, "Codigo Nome                                     Saldo              ValorTotalCheques"
						"        ValorTotalDepositos");
				cout << cWork << endl;

				sprintf_s(cWork, sizeof cWork, "%-6d %-40s %8.2f %15.2f %15.2f",stCliente.nCodigo, stCliente.CnomeCliente, 
					stCliente.dSaldo, stCliente.dVlrTotalCheques, stCliente.dVlrTotalDepositos);
				cout << cWork << endl;
				PAUSA;

				break;															// volta ao menu

			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;

				if(cOpcao == 's' || cOpcao == 'S')
					return;														// volta ao S.O.

				break;															// volta ao menu

			default:
				cout << "Digite uma opção válida!" << endl;
				PAUSA;
				break;															// volta ao menu

		} // switch

	} // while true

}// main