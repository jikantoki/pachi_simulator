//��`
#define CAPTION "�p�`�@�̐��������Č�����v���O����"
#define PRESENTER "Powered by �Ƃ����̂�"

#define BONUS_ONE 5//BONUS_IN��񂠂���̕�V�ʐ�
#define BONUS_IN_DEFAULT 30//bonus_in�̃f�t�H�l
#define HESO_BACK 2//�ւ��ɓ��������ɊҌ�����ʂ̐�

//�ǂݍ���
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//�t�@���N�V�����p
int random();
void rand_setup();

//�O���[�o���ϐ����g�킴��𓾂Ȃ�
int i_rand=114514;//srand���邽�тɑ��₵�Ă�
float f_rand=114514.0;//srand���邽�тɑ��₵�Ă�

int main(void){
	//�ϐ�������
	float rate=1;//���~�̑䂩�in�~�j
	unsigned int heso=25;//�ւ��ɓ���m���i1/n�j
	unsigned int chance=99;//�m���i1/n�j
	unsigned int in_st_chance=75;//�m�ϓ˓����i%�j;
	unsigned int st_chance=17;//�m�ώ��̊m���i1/n�j;
	unsigned int kakuhen_limit=50;;//1��̊m�ςŉ���񂹂邩�in��j;
	unsigned int count_heso=0,count_oatari=0,count_kakuhen=0,count_hazure=0,count_all=0;//���v�ւ�����񐔁A���v�哖����񐔁A���v�m�ω񐔁A���v�O��񐔁A�ł����ʂ̍��v��
	float money=0;//�����A�}�C�i�X�̏ꍇ�͎؋�������
	int i;//�ʏ펞��]�̃J�E���^
	int i_kakuhen=0;//�m�ώ��̃J�E���^
	int i_keizoku=0;//�{�[�i�X�p���̃J�E���^
	int kai_normal;//�ʏ펞�ɉ���񂷂�
	int bonus=0;//���̕�V���v�z
	int bonus_in=BONUS_IN_DEFAULT;//���̑哖����ŕ�V�����炦�錊�ɉ��ʓ�����邩�i�����_����+-10���x�ϓ�����j
	int bonus_in_cache;//��̂�𐳏�ɓ��������߂ɕK�v
	int kakuhen=0;//�m�ώ���1�ɂȂ�
	int kakuhen_flag=0;//�������m�ώ���1�ɂȂ�
	int keizoku_flag=0;//�{�[�i�X�p������1�ɂȂ�
	int kakuhen_mae=0;//�O��m�ς�������1�ɂȂ�
	int HESO_BACK_rate=HESO_BACK*rate;//�ւ��ɓ��ꂽ�ۂ̃L���b�V���o�b�N�̒l�i
	int horyu=0;//�m�ώ��ۗ̕��p
	
	//���A
	puts(CAPTION);
	puts(PRESENTER);
	
	//�����ݒ�
	printf("1/n ����������\nn%���S���������\n�͈͊O���͂͑����o�O��܂�\n");
	printf("���[�g�i0.1�A0.2�A0.5�A1�A2�A4�A5�A10�A25�~�Ȃǁj�H:");
	scanf("%f",&rate);
	HESO_BACK_rate=HESO_BACK*rate;
	printf("�ւ�����m���i1/ 19�`28�j�H:");
	scanf("%d",&heso);
	printf("�ʏ펞�m���i�Á�1/ 89 or 1/ 99�A�ʏ큨1/ 119�A��������1/319�j�H:");
	scanf("%d",&chance);
	printf("�m�ϓ˓����i50�`100 %%�j�H:");
	scanf("%d",&in_st_chance);
	printf("�m�ώ��̊m���i1/ 15�`20�j�H:");
	scanf("%d",&st_chance);
	printf("���̊m�ςŉ���񂹂邩�i30�`50 ��j�H:");
	scanf("%d",&kakuhen_limit);
	
	//�ݒ�m�F
	printf("\n-----------------------------\n");
	printf("�@�B�̃��[�g:\t%.2f�~\n",rate);
	printf("�ւ��ɓ���m��:\t1/%d\n",heso);
	printf("�ʏ펞�m��:\t1/%d\n",chance);
	printf("�m�ϓ˓���:\t1/%d\n",in_st_chance);
	printf("�m�ώ��̊m��:\t1/%d\n",st_chance);
	printf("���̊m�ςŉ񂹂��:\t%d��\n",kakuhen_limit);
	printf("-----------------------------\n\n");
	
	//�������烋�[�v
	while(1){
		printf("���ʑłi10000�ȏ�̓o�O�邩���A0�Ńv���O�����I���j�H:");
		scanf("%d",&kai_normal);
		if(kai_normal==0)break;
		kai_normal++;
		//�ł��n��
		for(i=1;i<kai_normal;i++){
			//printf("%d���...\n",i);
			money-=rate;//���Y����1�ʕ���v��
			count_all++;//�J�E���g�A�b�v
			if(random(heso,count_all+i+count_heso)==0){
				printf("%d��ڂłւ��ɓ���܂����A%d�~���Ҍ����܂��A���݂̏�����%.2f�~\n",count_all,HESO_BACK_rate,money+HESO_BACK_rate);
				count_heso++;
				money+=HESO_BACK_rate;//�ւ��ɓ�������n�ʊҌ�����
				if(random(chance,count_heso*count_all+money)==0){
					printf("%d��ڂő哖���肵�܂���\n",count_all);
					count_oatari++;//�哖����J�E���g
					rand_setup(count_all);
					bonus_in_cache=(rand()%20)-10;//�{�[�i�X�Ƀo���c�L����������
					bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//��̏����̑���
					bonus=bonus_in*BONUS_ONE*rate*chance*chance/100/100;
					money+=bonus;//���Y�Ƀ{�[�i�X��ǉ�����
					printf("%d�~���Q�b�g�I\n",bonus);
					bonus_in=BONUS_IN_DEFAULT;//�o���c�L�����Z�b�g
					
					//�m�ςɓ��邩�ǂ����̃C�t
					rand_setup(count_all);
					i_kakuhen=0;
					kakuhen=1;
					while(kakuhen==1){
						if(i_kakuhen==0){
							rand_setup(count_kakuhen+count_all+count_hazure+money*1.6);
							if(((rand()%100)+1)<=in_st_chance){
								kakuhen_flag=1;
								printf("%d��ڂŊm�ςɓ���܂���\n",count_all);
							}else{
								kakuhen_flag=0;
								printf("%d��ڂŊm�ϒ��Ɋm�ςɓ���܂���\n",count_all);
								count_oatari++;//�哖����J�E���g
								rand_setup(count_all);
								bonus_in_cache=(rand()%20)-10;//�{�[�i�X�Ƀo���c�L����������
								bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//��̏����̑���
								bonus=bonus_in*BONUS_ONE*rate*chance/100;
								money+=bonus;//���Y�Ƀ{�[�i�X��ǉ�����
								printf("%d�~���Q�b�g�I\n",bonus);
								bonus_in=BONUS_IN_DEFAULT;//�o���c�L�����Z�b�g
							}
						}else{
							rand_setup(count_kakuhen+count_all+count_hazure+money*3);
							if(((rand()%100)+1)<=(in_st_chance*0.7)){
								kakuhen_flag=1;
							}else{
								kakuhen_flag=0;
							}
						}
						if(kakuhen_flag==1){
							//��������m�ς̓��e
							kakuhen_mae=1;
							i_keizoku=0;
							count_kakuhen++;
							for(i_kakuhen=0;i_kakuhen<kakuhen_limit;i_kakuhen++){
								money-=rate;
								count_all++;
								if((random((heso/3),((count_kakuhen+count_heso+i_kakuhen+count_kakuhen+count_all+count_hazure+money)*1)))==0){
									if((random(1))==0){
										printf("%d��ڂŊm�ώ��ɂւ����͉E�ł��œ���܂����A%d�~���Ҍ����܂��A���݂̏�����%.2f�~\n",count_all,(HESO_BACK_rate*5),money+(HESO_BACK_rate*5));
										horyu=count_all;
										money+=(HESO_BACK_rate*5);//�ւ��ɓ�������n�ʊҌ�����
										count_heso++;
										if((random((st_chance),(count_heso*7+count_kakuhen*3+count_all+count_hazure+money*4)))==0){
											//�m�ώ��ɓ����������������
											count_oatari++;
											bonus_in_cache=(rand()%20)-10;//�{�[�i�X�Ƀo���c�L����������
											bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//��̏����̑���
											bonus=bonus_in*BONUS_ONE*rate*chance/100;
											money+=bonus;//���Y�Ƀ{�[�i�X��ǉ�����
											printf("%d�~���Q�b�g�I\n",bonus);
											bonus_in=BONUS_IN_DEFAULT;//�o���c�L�����Z�b�g
											//�{�[�i�X�p��
											keizoku_flag=1;
											while(keizoku_flag==1){
												count_all++;
												rand_setup(count_oatari*2+count_kakuhen+count_all+count_hazure+money*1.2);
												if(i_keizoku==0){
													if(((rand()%100)+1)<=(in_st_chance*1)){
														keizoku_flag=1;
													}else{
														keizoku_flag=0;
													}
												}else{
													if(((rand()%100)+1)<=(in_st_chance*(1/2.0))){
														keizoku_flag=1;
													}else{
														keizoku_flag=0;
													}
												}
												if(keizoku_flag==1){
													printf("�{�[�i�X�p���I�i%d��ځj\n",i_keizoku+1);
													i_keizoku++;
													count_oatari++;
													rand_setup(count_all);
													bonus_in_cache=(rand()%20)-10;//�{�[�i�X�Ƀo���c�L����������
													bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//��̏����̑���
													bonus=bonus_in*BONUS_ONE*rate*chance/100;
													money+=bonus;//���Y�Ƀ{�[�i�X��ǉ�����
													printf("%d�~���Q�b�g�I\n",bonus);
													bonus_in=BONUS_IN_DEFAULT;//�o���c�L�����Z�b�g
												}else{
													printf("�{�[�i�X�͌p�����܂���ł���\n");
												}
											}
										}else{
											i++;
											count_hazure++;
										}
									}
									
								}else{
									i++;
									count_hazure++;
								}
							}
						}else{
							kakuhen=0;//�m�ϏI��
							if(kakuhen_mae==1){
								printf("%d��ڂŊm�ς��I�����܂���\n",count_all);
								horyu=0;
							}else{
								horyu=0;
								printf("�m�ς͋N���܂���ł���\n");
							}
							kakuhen_mae=0;
						}
					}
				}
			}else{
				count_hazure++;
			}
		}
		printf("%d��ڂ���%d��ł��܂���\n",count_all-i+1,i-1);
		
		//����
		printf("\n-----------------------------\n");
		printf("����܂ł̌���\n");
		printf("�@�B�̃��[�g:\t%.2f�~\n",rate);
		printf("�ւ��ɓ���m��:\t1/%d\n",heso);
		printf("�ʏ펞�m��:\t1/%d\n",chance);
		printf("�m�ϓ˓���:\t%d%%\n",in_st_chance);
		printf("�m�ώ��̊m��:\t1/%d\n",st_chance);
		printf("���̊m�ςŉ���񂹂邩:\t%d��\n",kakuhen_limit);
		puts("");
		printf("�ւ������:\t%d��\n",count_heso);
		printf("�哖�����:\t%d��\n",count_oatari);
		printf("�m�ς̉�:\t%d��\n",count_kakuhen);
		printf("�O���:\t%d��\n",count_hazure);
		printf("���v��:\t%d��\n",count_all);
		if(money<0){
			printf("�Ԏ�:\t%f�~\n",money);
		}else{
			printf("����:\t%f�~\n",money);
		}
		printf("-----------------------------\n\n");
	}
	
	//�ŏI����
	printf("\n-----------------------------\n");
	printf("�ŏI����\n");
	printf("�@�B�̃��[�g:\t%.2f�~\n",rate);
	printf("�ւ��ɓ���m��:\t1/%d\n",heso);
	printf("�ʏ펞�m��:\t1/%d\n",chance);
	printf("�m�ϓ˓���:\t%d%%\n",in_st_chance);
	printf("�m�ώ��̊m��:\t1/%d\n",st_chance);
	printf("���̊m�ςŉ���񂹂邩:\t%d��\n",kakuhen_limit);
	puts("");
	//count_heso=0,count_oatari=0,count_hazure=0,count_all=0
	printf("�ւ������:\t%d��\n",count_heso);
	printf("�哖�����:\t%d��\n",count_oatari);
	printf("�m�ς̉�:\t%d��\n",count_kakuhen);
	printf("�O���:\t%d��\n",count_hazure);
	printf("���v��:\t%d��\n",count_all);
	if(money<0){
		printf("�Ԏ�:\t%f�~\n",money);
	}else{
		printf("����:\t%f�~\n",money);
	}
	printf("-----------------------------\n\n");
	
	printf("�v���O�������I�����܂�\n");
	return 0;
}
int random(int input,int randomizer){// 1/n�̊m����return 0��Ԃ��A����1��Ԃ�
	int output=0;
	rand_setup(randomizer);
	output=rand()%input;
	if (output==0)return 0;
	return 1;
}
void rand_setup(int randomizer){
	int output=0;
	if(i_rand>1000000){
		i_rand=0;
	}else{
		i_rand++;
	}
	if(f_rand>1000000.0){
		f_rand=0;
	}else{
		f_rand+=3.1415;
	}
	if(randomizer==0){
		srand(time(NULL)+i_rand+f_rand);
	}else{
		srand(time(NULL)+randomizer+i_rand+f_rand);
	}
	return;
}