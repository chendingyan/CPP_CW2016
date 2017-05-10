#include "BadPigObject.h"
#include "templates.h"
#include "header.h"
#include "DiamondObject.h"
#include "PigObject.h"
#include <time.h>
BadPigObject::BadPigObject(GoldMinerEngine *pEngine, int sizeX, int sizeY, int posX, int posY, int speed)
	: DynamicObject(pEngine, sizeX, sizeY, posX, posY, speed)
	, m_pEngine(pEngine)
	, direction(1)
	, diamond_help(0)
	, min(1000000)
	, updown(0)
	, starttime(0)
	, score(0)
	, rate(10)
	, genmax(500)
{
	diamond_loc[0] = 0;
	diamond_loc[1] = 0;
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = posX;
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = posY;
	//we also need space for numbers on the pig
	m_iDrawWidth = m_SizeX;
	m_iDrawHeight = m_SizeY;
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	prl1.LoadImage("./img/badpig_left1.png");
	prr1.LoadImage("./img/badpig_right1.png");
	prl2.LoadImage("./img/badpig_left2.png");
	prr2.LoadImage("./img/badpig_right2.png");
	prl3.LoadImage("./img/badpig_left3.png");
	prr3.LoadImage("./img/badpig_right3.png");
	num_diamond = readDiamondPos();
	SetVisible(true);

}


BadPigObject::~BadPigObject()
{
}


void BadPigObject::Draw()
{
	if (!IsVisible()){
		return;
	}
	switch (m_mode)
	{
	case 0:
		switch (direction)
		{
		case 1: // go left
			if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 0 && (static_cast<int> (m_iCurrentScreenX) % 9) < 3){
				prl1.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prl1.GetWidth(), prl1.GetHeight());
			}
			else if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 3 && (static_cast<int> (m_iCurrentScreenX) % 9) < 6){
				prl2.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prl2.GetWidth(), prl2.GetHeight());
			}
			else{
				prl3.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prl3.GetWidth(), prl3.GetHeight());
			}
			break;
		case 2: // go right
			if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 0 && (static_cast<int> (m_iCurrentScreenX) % 9) < 3){
				prr1.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prr1.GetWidth(), prr1.GetHeight());
			}
			else if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 3 && (static_cast<int> (m_iCurrentScreenX) % 9) < 6){
				prr2.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prr2.GetWidth(), prr2.GetHeight());
			}
			else{
				prr3.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prr3.GetWidth(), prr3.GetHeight());
			}
			break;
		}

	case 1: //be caught
		if (direction == 0){
			prr2.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, prr2.GetWidth(), prr2.GetHeight());
		}

		break;
	case 2:
		char buf[100];
		sprintf(buf, "+%d points!", score);
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buf, 0xff0000);
		break;
	default:
		break;
	}
}


void BadPigObject::DoUpdate(int iCurrentTime)
{
	
	int starttime = 0;
	if (!IsVisible()){
		return;
	}
	if (!isfirst){
		work();
		isfirst = true;
		
	}
	DiamondObject* obj;
	int count;
	for (count = 1; count < num_diamond; count++){
		obj = dynamic_cast<DiamondObject *>(m_pEngine->GetDisplayableObject(BestRooting[count] + m_pEngine->gs_num));
		if (obj != NULL && !obj->IsVisible()){
			continue;
		}
		if (obj != NULL){
			break;
		}
		
		
	}
	if (count != num_diamond){
		if (m_iCurrentScreenX < obj->GetXCentre() - 2){
			m_iCurrentScreenX++;
		}
		else if (m_iCurrentScreenX > obj->GetXCentre() + 2){
			m_iCurrentScreenX--;
		}
		if (m_iCurrentScreenY < obj->GetYCentre() - 2){
			m_iCurrentScreenY++;
		}
		else if (m_iCurrentScreenY > obj->GetYCentre() + 2){
			m_iCurrentScreenY--;
		}
		if (m_iCurrentScreenX <= 0){
			m_iCurrentScreenX++;
		}
		if (m_iCurrentScreenX >= 800){
			m_iCurrentScreenX--;
		}
		if (m_iCurrentScreenY >= 600){
			m_iCurrentScreenY--;
		}
		if (m_iCurrentScreenY <= 150){
			m_iCurrentScreenY++;
		}
		if (m_iCurrentScreenX >= obj->GetXCentre() - 2 && m_iCurrentScreenX <= obj->GetXCentre() + 2 && m_iCurrentScreenY >= obj->GetYCentre() - 2 && m_iCurrentScreenY <= obj->GetYCentre() + 2){
			if (GetEngine()->GetTime() - starttime >= 2000){
				m_pEngine->StoreObjectInArray(BestRooting[count] + m_pEngine->gs_num, NULL);
				starttime = GetEngine()->GetTime();
			}
		}
	}
	
	//if (diamond_help != -1){
	//	DiamondSearchAlgorithm();
	//}

	//if (diamond_loc[0] != 0){
	//	m_mode = HookableObject::isHooked();
	//	if (diamond_help == 0){
	//		if (m_iCurrentScreenX < diamond_loc[0]){
	//			m_iCurrentScreenX++;
	//			direction = 2;//right
	//			if (m_iCurrentScreenY < diamond_loc[1]){
	//				m_iCurrentScreenY++;
	//			}
	//			else if (m_iCurrentScreenY> diamond_loc[1]){
	//				m_iCurrentScreenY--;
	//			}
	//		}
	//		else{
	//			m_iCurrentScreenX--;
	//			direction = 1;
	//			if (m_iCurrentScreenY < diamond_loc[1]){
	//				m_iCurrentScreenY++;
	//			}
	//			else{
	//				m_iCurrentScreenY--;
	//			}
	//		}
	//	}
	//	else{
	//		updown++;
	//		if ((int)(iCurrentTime / 500) % 2 == 0){
	//			m_iCurrentScreenY++;
	//		}
	//		else{
	//			m_iCurrentScreenY--;
	//		}
	//	}
	//	RedrawObjects();
	//}
	//else{
	//	switch (direction)
	//	{
	//	case 1:
	//		m_iCurrentScreenX -= m_speed;
	//		if (m_iCurrentScreenX < 10){
	//			direction = 2;
	//		}
	//		for (int i = 1; i < m_pEngine->obj_num; i++){
	//			HookableObject * obj = dynamic_cast<HookableObject*> (GetEngine()->GetDisplayableObject(i));
	//			if (obj != NULL){
	//				if (CollsionDetection(obj)){
	//					direction = 2;
	//				}
	//			}
	//			
	//		}
	//		break;
	//	case 2:
	//		iCurrentScreenX += m_speed;
	//		m_iCurrentScreenX = iCurrentScreenX;
	//		if (iCurrentScreenX > 720){
	//			direction = 1;
	//		}
	//		for (int i = 1; i < m_pEngine->obj_num; i++){
	//			HookableObject* obj = dynamic_cast<HookableObject*> (GetEngine()->GetDisplayableObject(i));
	//			if (obj != NULL){
	//				if (CollsionDetection(obj)){
	//					direction = 1;
	//				}
	//			}
	//			
	//		}
	//		break;
	//	default:
	//		break;
	//	}
		m_mode = isHooked();
	//}
}


void BadPigObject::DiamondSearchAlgorithm()
{
	num_of_diamond = m_pEngine->diamond_num;
	int obj_num = m_pEngine->obj_num;
	int gs_num = m_pEngine->gs_num;
	int counter = 0;
	int diamond_visit = 0;
	DisplayableObject * object;

	for (int i = gs_num+1; i <= obj_num; i++){
		object = m_pEngine->GetDisplayableObject(i);
		DiamondObject * diamond = dynamic_cast<DiamondObject *>(object);

		if (diamond == NULL){
			return;
		}
		int dx = diamond->m_PosX;
		int dy = diamond->m_PosY;
		if (diamond->IsVisible()){
			if (m_mode != 0){
				diamond->pigLeaves();
				diamond_loc[0] = 0;
				diamond_help = -1;
				return;
			}

			if (diamond_help == 0){
				if (m_iCurrentScreenX < dx + 2 && m_iCurrentScreenY < dy + 2 && m_iCurrentScreenY > dy - 2 && m_iCurrentScreenX > dx - 2){
					diamond_help = 1;
					diamond->PigComes();
				}
				counter = 0;
				int distance = (m_iCurrentScreenX - dx)*(m_iCurrentScreenX - dx) + (m_iCurrentScreenY - dy)*(m_iCurrentScreenY - dy);

				if (distance < min){
					min = distance;
					diamond_loc[counter] = dx;
					counter++;
					diamond_loc[counter] = dy;
				}
			}
			else{
				if (updown > 40 && diamond->arrived == 1){
					diamond->pigWaits();
					updown = 0;
				}
			}
		}
		else{
			diamond_visit++;
			if (diamond->arrived == 1){
				diamond->pigLeaves();
				diamond_help = 0;
			}
			if (dx == diamond_loc[0] && dy == diamond_loc[1]){
				diamond_loc[0] = 0;
				diamond_loc[1] = 1;
				min = 1000000;
				diamond_help = 0;
			}
		}
	}
	if (diamond_visit == num_of_diamond){
		diamond_help = -1;
	}
}


int BadPigObject::readDiamondPos()
{
	num_of_diamond = m_pEngine->diamond_num;
	int obj_num = m_pEngine->obj_num;
	int gs_num = m_pEngine->gs_num;
	num_diamond = 1;
	DisplayableObject * object;
	diamonds.push_back(*new Point(0, m_PosX, m_PosY));
	for (int i = gs_num + 1; i <= obj_num; i++){
		object = m_pEngine->GetDisplayableObject(i);
		DiamondObject * diamond = dynamic_cast<DiamondObject *>(object);
		if (diamond != NULL){
			diamonds.push_back(*new Point(i - gs_num, diamond->GetXCentre(), diamond->GetYCentre()));
			num_diamond++;
		}
	}
	return num_diamond;
}


void BadPigObject::initDistMatrix()
{
	int temp_x, temp_y;
	printf("%d", num_diamond);
	point_distance = new double*[num_diamond];
	for (int i = 0; i < num_diamond; i++){
		point_distance[i] = new double[num_diamond];
		for (int j = 0; j < num_diamond; j++){
			temp_x = diamonds.at(j).getx() - diamonds.at(i).getx();
			temp_y = diamonds.at(j).gety() - diamonds.at(i).gety();
			point_distance[i][j] = sqrt(temp_x * temp_x + temp_y * temp_y);
		}
	}
}

//check if the new point is already in the current population, 0 is the default start point
bool BadPigObject::check(int pop, int num, int k)
{
	int i;
	for (i = 0; i <= num; i++)
	{
		if (k == group[pop][i])
			return true;
	}
	return false;
}


void BadPigObject::InitColony()
{
	int i, j, r;
	for (i = 0; i<POPSIZE; i++)
	{
		group[i] = new int[num_diamond + 1];
		group[i][0] = 0;
		group[i][num_diamond] = 0;
	}
	BestValue = MAXVALUE;
	BestFitness = 0;
	for (i = 0; i<POPSIZE; i++)
	{
		for (j = 1; j<num_diamond; j++)
		{
			r = rand() % (num_diamond - 1) + 1;//产生1～CITY_NUM-1之间的随机数
			while (check(i, j, r))
			{
				r = rand() % (num_diamond - 1) + 1;
			}
			group[i][j] = r;
		}
	}
}


void BadPigObject::CalFitness()
{
	int i, j;
	int start, rear;
	double Distance[POPSIZE];
	for (i = 0; i<POPSIZE; i++)
	{
		//求适应值
		Distance[i] = 0;
		for (j = 1; j <= num_diamond; j++)
		{
			start = group[i][j - 1];   //city->colony[i][j-1];
			rear = group[i][j];      //city->colony[i][j];
			Distance[i] += point_distance[start][rear];
		}
		fitness[i] = N / (Distance[i]);

	}
	double k = fitness[0];        //city->fitness[0];
	int best = 0;               //种群中最好的那一个路径的下标
	for (i = 1; i<POPSIZE; i++)
	{
		if (k<fitness[i]){
			k = fitness[i];
			best = i;
		}
	}
	//如果是最优值，更新最优值
	if (k > BestFitness) {
		BestFitness = k;     //city->BestFitness = k;
		BestValue = Distance[best];     //city->BestValue = city->Distance[best];
		printf("Best -------- %f\n", BestValue);
		for (i = 0; i <= num_diamond; i++) {
			BestRooting = group[best];
		}
	}
}


void BadPigObject::Select()
{
	int **newGroup = new int*[POPSIZE];
	for (int i = 0; i < POPSIZE; i++){
		newGroup[i] = new int[num_diamond+1];
	}
	//计算总适应度之和
	double allfitness = 0;
	for (int i = 0; i < POPSIZE; i++) {
		allfitness += fitness[i];
	}
	int cnt = 0;
	//开始选择，随机生成随机数，用轮盘赌算法，选择出来POPSIZE大小的种群
	puts("Begin Select...");
	while (cnt < POPSIZE)
	{
		double r = rand() % (100) / (double)(100);        //100??
		double sum = 0;
		int i;
		for (i = 0; i < POPSIZE; i++)
		{
			sum += fitness[i] / allfitness;     //city->fitness[i]/allfitness;
			if (r < sum)
			{
				break;
			}
		}
		//cout << r << " " << sum << " " << i << endl;
		//先将选择出来的值放到一个临时数组中
		for (int j = 0; j <= num_diamond; j++)
		{
			newGroup[cnt][j] = group[i][j];
		}

		cnt++;
	}
	//Update population
	for (int x = 0; x < POPSIZE; x++)
	{
		for (int y = 0; y <= num_diamond; y++)
		{
			group[x][y] = newGroup[x][y];
		}
	}

}


void BadPigObject::OXCross(int i)
{
	int *pop1 = new int [num_diamond];
	int *pop2 = new int [num_diamond];
	//生成两个随机数
	int r1 = rand() % (num_diamond - 1) + 1;
	int r2 = rand() % (num_diamond - 1) + 1;
	if (r1 > r2) swap(r1, r2);
	//将随机数之间的进行交换，放到最左边
	//然后把原种群放在最右边，并去掉重复的城市
	int len = r2 - r1 + 1;
	//对种群一的操作
	for (int j = 1; j <= len; j++)
	{
		pop1[j] = group[i + 1][r1 + j - 1];
		pop2[j] = group[i][r1 + j - 1];
	}
	int j = len + 1;
	int cnt = 1;

	while (j < num_diamond && cnt < num_diamond)
	{
		int flag = 1;
		for (int k = 1; k < j; k++)
		{
			if (pop1[k] == group[i][cnt]) flag = 0;        //city->colony[i][cnt]
		}
		if (flag)
		{
			pop1[j] = group[i][cnt];       //city->colony[i][cnt];
			j++;
		}
		cnt++;

	}
	//对种群2的操作
	j = len + 1;
	cnt = 1;
	while (j < num_diamond && cnt < num_diamond)
	{
		int flag = 1;
		for (int k = 1; k < j; k++)
		{
			if (pop2[k] == group[i + 1][cnt]) flag = 0;  //city->colony[i+1][cnt]
		}
		if (flag)
		{
			pop2[j] = group[i + 1][cnt];     //city->colony[i+1][cnt];
			j++;
		}
		cnt++;

	}
	for (int j = 1; j < num_diamond; j++)
	{
		group[i][j] = pop1[j];  //city->colony[i][j] = pop1[j];
		group[i + 1][j] = pop2[j];    //city->colony[i+1][j] = pop2[j];
	}
}


void BadPigObject::Cross(double pc)
{
	for (int i = 0; i < POPSIZE; i += 2)
	{
		double r = rand() % (100) / (double)(100);
		if (r < pc)
		{
			puts("Begin Cross...");
			//printf("个体%d与个体%d进行交叉", i, i+1);
			OXCross(i);
		}
	}
}


void BadPigObject::OnCVariation(int i)
{
	int k = rand() % (num_diamond - 1) + 1;
	//printf("population %d %dtimes Vriation\n", i, k);
	for (int j = 1; j <= k; j++)
	{
		//随机选两个点进行交换变异操作
		int r1 = rand() % (num_diamond - 1) + 1;
		int r2 = rand() % (num_diamond - 1) + 1;
		while (r1 == r2)
		{
			r2 = rand() % (num_diamond - 1) + 1;
		}
		int temp = group[i][r1];   //int tmp = city->colony[i][r1];
		group[i][r1] = group[i][r2];  //city->colony[i][r1] = city->colony[i][r2];
		group[i][r2] = temp;    //city->colony[i][r2] = tmp;
	}
}


void BadPigObject::Mutation(double pm)
{
	for (int i = 0; i < POPSIZE; i++)
	{
		double r = rand() % (100) / (double)(100);
		if (r < pm)
		{
			puts("Begin Mutation...");
			OnCVariation(i);
		}
	}
}


void BadPigObject::OutPut()
{
	if (BestRooting != NULL){
		for (int i = 0; i<num_diamond + 1; i++){
			printf("%5d", BestRooting[i]);
		}
	}
	printf("\n");
}


void BadPigObject::work()
{
	int i;
	seed = (unsigned)time(0);
	srand(seed);

	MaxEpoc = 2000;
	pcross = 0.6;
	pmutation = 0.05;
	initDistMatrix();//求城市间两两之间的距离

	InitColony();//生成初始种群
	printf("hi");
	CalFitness();//计算适应值,考虑应该在这里面把最优选出来
	OutPut();
	for (i = 0; i<MaxEpoc; i++)
	{
		printf("%d time Population iteration\n", i);
		Select();//选择(复制)
		Cross(pcross);//交叉
		Mutation(pmutation);//变异
		CalFitness();//计算适应值
	}
	OutPut();//输出
}
