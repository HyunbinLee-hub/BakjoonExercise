#include <stdio.h>
#include <stdlib.h>

// 입력한 이름과 ID 번호 저장
struct ssu_id {
	char name[64];
	int id;
};

// 입력한 값을 파일에 저장 후, 파일로부터 다시 읽어와서 출력
int main(void)
{
	struct ssu_id test1, test2;
	char *fname = "ssu_exam.dat";
	FILE *fp;

	// 쓰기 전용 파일 오픈, 파일이 없을 시 생성, 오픈 실패 시 에러처리
	if ((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	// 입력한 ID, 이름을 구조체 멤버 변수에 저장
	printf("Input ID>> ");
	scanf("%d", &test1.id);
	printf("Input name>> ");
	scanf("%s", test1.name);

	// 구조체의 데이터를 오픈한 파일에 write하여 저장
	if (fwrite(&test1, sizeof(struct ssu_id), 1, fp) != 1)
	{
		fprintf(stderr, "fwrite error\n");
		exit(1);
	}

	fclose(fp);

	// 쓰기를 수행한 파일을 읽기 전용으로 오픈
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	// 파일의 데이터를 구조체 단위로 읽어오기
	if (fread(&test2, sizeof(struct ssu_id), 1, fp) != 1) {
		fprintf(stderr, "fread error\n");
		exit(1);
	}

	// 읽어온 파일의 데이터를 출력
	printf("\nID	name\n");
	printf(" ============\n");
	printf("%d	%s\n", test2.id, test2.name);

	fclose(fp);
	exit(0);
}
