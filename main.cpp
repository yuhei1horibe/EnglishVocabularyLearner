

#include"word.h"


int main(void)
{
	//��萔�����
	int		n;
	//������̓���
	char	str[32];

	WORD_DATA	data;
	int			EFlag;

	//�f�[�^�x�[�X�Ǘ��C���^�[�t�F�C�X�ւ̃|�C���^
	DATABASE*	DataBase;
	DATA_IO		DataIO;
	QUIZ		Quiz;

	system("title English Word Expert");

	//�f�[�^�x�[�X�Ǘ��N���X���C���X�^���X��
	if( (DataBase = DataBase->GetInstance()) == NULL)
	{
		cout << "Error\n";
		return 0;
	}

	cout << "�ǂݍ��ރt�@�C�������w�肵�Ă��������B\n";
	cin.getline(str, 32);

	//�ǂݍ��ރt�@�C�����w��
	if(DataIO.Init(str))
	{
		getch();
		return 0;
	}

	//�t�@�C������f�[�^��ǂݍ���
	while( (EFlag = DataIO.ReadFromFile(&data)) == 0)
	{
		//�P����f�[�^�x�[�X�ɓo�^
		if(DataBase->Entry(&data) == -1)
		{
			cout << "Error\n";
			getch();
			return 0;
		}
	}

	if(EFlag == -1)
	{
		cout << "�ǂݍ��݃G���[\n";
		return 0;
	}

	system("cls");
	DataBase->display_number();
	cout << "\n\n\tPress any key.\n\n";
	getch();
	system("cls");

	//�f�[�^��O����Ƀ����_���\�[�g
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);

	//�������[�v
	while(1)
	{
		system("cls");

		cout << "\n\n�����邩�w�肵�Ă��������B\n�I������ꍇ��0����͂��Ă��������B\n";

		cin.getline(str, 32);
		n	= atoi(str);

		if(n == 0)
			break;

		system("cls");

		for(int i = 0; i < n; i++)
		{
			//���\��
			if(EFlag = Quiz.Display(DataBase))
			{
				if(EFlag == -1)
				{
					cout << "\n\n\t�G���[���������܂����B�v���O�����𒆒f���܂��B\n";
					getch();
					break;
				}

				else
				{
					//�f�[�^�x�[�X�̏I�[�ɒB�����烊�X�g���\�[�g���Ă�蒼��
					DataBase->Sort(RANDOM, EFlag);

					//��萔�����ɖ߂����߂Ƀ��[�v�ϐ����f�N�������g
					i--;
					system("cls");
				}
			}
		}
		//���ʂ�\�����A�|�C���^���������B���_��������
		Quiz.Result();
		getch();
		DataBase->ResetPointer();
		Quiz.Reset();
	}
	return 0;
}
