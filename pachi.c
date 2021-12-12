//定義
#define CAPTION "パチ機の数字だけ再現するプログラム"
#define PRESENTER "Powered by ときえのき"

#define BONUS_ONE 5//BONUS_IN一回あたりの報酬玉数
#define BONUS_IN_DEFAULT 30//bonus_inのデフォ値
#define HESO_BACK 2//へそに入った時に還元する玉の数

//読み込み
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//ファンクション用
int random();
void rand_setup();

//グローバル変数も使わざるを得ない
int i_rand=114514;//srandするたびに増やしてく
float f_rand=114514.0;//srandするたびに増やしてく

int main(void){
	//変数初期化
	float rate=1;//何円の台か（n円）
	unsigned int heso=25;//へそに入る確率（1/n）
	unsigned int chance=99;//確率（1/n）
	unsigned int in_st_chance=75;//確変突入率（%）;
	unsigned int st_chance=17;//確変時の確率（1/n）;
	unsigned int kakuhen_limit=50;;//1回の確変で何回回せるか（n回）;
	unsigned int count_heso=0,count_oatari=0,count_kakuhen=0,count_hazure=0,count_all=0;//合計へそ入り回数、合計大当たり回数、合計確変回数、合計外れ回数、打った玉の合計数
	float money=0;//資金、マイナスの場合は借金をする
	int i;//通常時回転のカウンタ
	int i_kakuhen=0;//確変時のカウンタ
	int i_keizoku=0;//ボーナス継続のカウンタ
	int kai_normal;//通常時に何回回すか
	int bonus=0;//一回の報酬合計額
	int bonus_in=BONUS_IN_DEFAULT;//一回の大当たりで報酬がもらえる穴に何玉入れられるか（ランダムで+-10程度変動あり）
	int bonus_in_cache;//上のやつを正常に動かすために必要
	int kakuhen=0;//確変時に1になる
	int kakuhen_flag=0;//こいつも確変時に1になる
	int keizoku_flag=0;//ボーナス継続時に1になる
	int kakuhen_mae=0;//前回確変だったら1になる
	int HESO_BACK_rate=HESO_BACK*rate;//へそに入れた際のキャッシュバックの値段
	int horyu=0;//確変時の保留用
	
	//挨拶
	puts(CAPTION);
	puts(PRESENTER);
	
	//初期設定
	printf("1/n →分母を入力\nn%→百分率を入力\n範囲外入力は多分バグります\n");
	printf("レート（0.1、0.2、0.5、1、2、4、5、10、25円など）？:");
	scanf("%f",&rate);
	HESO_BACK_rate=HESO_BACK*rate;
	printf("へそ入り確率（1/ 19～28）？:");
	scanf("%d",&heso);
	printf("通常時確率（甘→1/ 89 or 1/ 99、通常→1/ 119、厳しい→1/319）？:");
	scanf("%d",&chance);
	printf("確変突入率（50～100 %%）？:");
	scanf("%d",&in_st_chance);
	printf("確変時の確率（1/ 15～20）？:");
	scanf("%d",&st_chance);
	printf("一回の確変で何回回せるか（30～50 回）？:");
	scanf("%d",&kakuhen_limit);
	
	//設定確認
	printf("\n-----------------------------\n");
	printf("機械のレート:\t%.2f円\n",rate);
	printf("へそに入る確率:\t1/%d\n",heso);
	printf("通常時確率:\t1/%d\n",chance);
	printf("確変突入率:\t1/%d\n",in_st_chance);
	printf("確変時の確率:\t1/%d\n",st_chance);
	printf("一回の確変で回せる回数:\t%d回\n",kakuhen_limit);
	printf("-----------------------------\n\n");
	
	//ここからループ
	while(1){
		printf("何玉打つ（10000以上はバグるかも、0でプログラム終了）？:");
		scanf("%d",&kai_normal);
		if(kai_normal==0)break;
		kai_normal++;
		//打ち始め
		for(i=1;i<kai_normal;i++){
			//printf("%d回目...\n",i);
			money-=rate;//資産から1玉分を没収
			count_all++;//カウントアップ
			if(random(heso,count_all+i+count_heso)==0){
				printf("%d回目でへそに入りました、%d円を還元します、現在の所持金%.2f円\n",count_all,HESO_BACK_rate,money+HESO_BACK_rate);
				count_heso++;
				money+=HESO_BACK_rate;//へそに入ったらn玉還元する
				if(random(chance,count_heso*count_all+money)==0){
					printf("%d回目で大当たりしました\n",count_all);
					count_oatari++;//大当たりカウント
					rand_setup(count_all);
					bonus_in_cache=(rand()%20)-10;//ボーナスにバラツキを持たせる
					bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//上の処理の続き
					bonus=bonus_in*BONUS_ONE*rate*chance*chance/100/100;
					money+=bonus;//資産にボーナスを追加投入
					printf("%d円をゲット！\n",bonus);
					bonus_in=BONUS_IN_DEFAULT;//バラツキをリセット
					
					//確変に入るかどうかのイフ
					rand_setup(count_all);
					i_kakuhen=0;
					kakuhen=1;
					while(kakuhen==1){
						if(i_kakuhen==0){
							rand_setup(count_kakuhen+count_all+count_hazure+money*1.6);
							if(((rand()%100)+1)<=in_st_chance){
								kakuhen_flag=1;
								printf("%d回目で確変に入りました\n",count_all);
							}else{
								kakuhen_flag=0;
								printf("%d回目で確変中に確変に入りました\n",count_all);
								count_oatari++;//大当たりカウント
								rand_setup(count_all);
								bonus_in_cache=(rand()%20)-10;//ボーナスにバラツキを持たせる
								bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//上の処理の続き
								bonus=bonus_in*BONUS_ONE*rate*chance/100;
								money+=bonus;//資産にボーナスを追加投入
								printf("%d円をゲット！\n",bonus);
								bonus_in=BONUS_IN_DEFAULT;//バラツキをリセット
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
							//ここから確変の内容
							kakuhen_mae=1;
							i_keizoku=0;
							count_kakuhen++;
							for(i_kakuhen=0;i_kakuhen<kakuhen_limit;i_kakuhen++){
								money-=rate;
								count_all++;
								if((random((heso/3),((count_kakuhen+count_heso+i_kakuhen+count_kakuhen+count_all+count_hazure+money)*1)))==0){
									if((random(1))==0){
										printf("%d回目で確変時にへそ又は右打ちで入りました、%d円を還元します、現在の所持金%.2f円\n",count_all,(HESO_BACK_rate*5),money+(HESO_BACK_rate*5));
										horyu=count_all;
										money+=(HESO_BACK_rate*5);//へそに入ったらn玉還元する
										count_heso++;
										if((random((st_chance),(count_heso*7+count_kakuhen*3+count_all+count_hazure+money*4)))==0){
											//確変時に当たりを引いた処理
											count_oatari++;
											bonus_in_cache=(rand()%20)-10;//ボーナスにバラツキを持たせる
											bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//上の処理の続き
											bonus=bonus_in*BONUS_ONE*rate*chance/100;
											money+=bonus;//資産にボーナスを追加投入
											printf("%d円をゲット！\n",bonus);
											bonus_in=BONUS_IN_DEFAULT;//バラツキをリセット
											//ボーナス継続
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
													printf("ボーナス継続！（%d回目）\n",i_keizoku+1);
													i_keizoku++;
													count_oatari++;
													rand_setup(count_all);
													bonus_in_cache=(rand()%20)-10;//ボーナスにバラツキを持たせる
													bonus_in=BONUS_IN_DEFAULT+bonus_in_cache;//上の処理の続き
													bonus=bonus_in*BONUS_ONE*rate*chance/100;
													money+=bonus;//資産にボーナスを追加投入
													printf("%d円をゲット！\n",bonus);
													bonus_in=BONUS_IN_DEFAULT;//バラツキをリセット
												}else{
													printf("ボーナスは継続しませんでした\n");
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
							kakuhen=0;//確変終了
							if(kakuhen_mae==1){
								printf("%d回目で確変が終了しました\n",count_all);
								horyu=0;
							}else{
								horyu=0;
								printf("確変は起きませんでした\n");
							}
							kakuhen_mae=0;
						}
					}
				}
			}else{
				count_hazure++;
			}
		}
		printf("%d回目から%d回打ちました\n",count_all-i+1,i-1);
		
		//結果
		printf("\n-----------------------------\n");
		printf("今回までの結果\n");
		printf("機械のレート:\t%.2f円\n",rate);
		printf("へそに入る確率:\t1/%d\n",heso);
		printf("通常時確率:\t1/%d\n",chance);
		printf("確変突入率:\t%d%%\n",in_st_chance);
		printf("確変時の確率:\t1/%d\n",st_chance);
		printf("一回の確変で何回回せるか:\t%d回\n",kakuhen_limit);
		puts("");
		printf("へそ入り回数:\t%d回\n",count_heso);
		printf("大当たり回数:\t%d回\n",count_oatari);
		printf("確変の回数:\t%d回\n",count_kakuhen);
		printf("外れ回数:\t%d回\n",count_hazure);
		printf("合計回数:\t%d回\n",count_all);
		if(money<0){
			printf("赤字:\t%f円\n",money);
		}else{
			printf("黒字:\t%f円\n",money);
		}
		printf("-----------------------------\n\n");
	}
	
	//最終結果
	printf("\n-----------------------------\n");
	printf("最終結果\n");
	printf("機械のレート:\t%.2f円\n",rate);
	printf("へそに入る確率:\t1/%d\n",heso);
	printf("通常時確率:\t1/%d\n",chance);
	printf("確変突入率:\t%d%%\n",in_st_chance);
	printf("確変時の確率:\t1/%d\n",st_chance);
	printf("一回の確変で何回回せるか:\t%d回\n",kakuhen_limit);
	puts("");
	//count_heso=0,count_oatari=0,count_hazure=0,count_all=0
	printf("へそ入り回数:\t%d回\n",count_heso);
	printf("大当たり回数:\t%d回\n",count_oatari);
	printf("確変の回数:\t%d回\n",count_kakuhen);
	printf("外れ回数:\t%d回\n",count_hazure);
	printf("合計回数:\t%d回\n",count_all);
	if(money<0){
		printf("赤字:\t%f円\n",money);
	}else{
		printf("黒字:\t%f円\n",money);
	}
	printf("-----------------------------\n\n");
	
	printf("プログラムを終了します\n");
	return 0;
}
int random(int input,int randomizer){// 1/nの確率でreturn 0を返す、他は1を返す
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