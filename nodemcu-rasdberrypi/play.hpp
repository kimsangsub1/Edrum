#include "record.h"
#include <fstream>

class Serial_play
{
    //현재 참조하고 있는 파일의 번호.
    int current_filenum;
    //현재 참조하고 있는 파일의 이름
    char current_filename[50];
    //파일의 수행가능 여부
    bool playable;

    //현재 채점 중인지 여부
    bool playing;

    //현재 참조하고 있는 파일에서 가져온 노트 배열.
    note* drum[2];
    int drum_cnt[2];

    //현재 참조하고 있는 파일 스트림
    std::ifstream fp;
    
    //노트 배열 할당 해제
    void deallocation();

    //현재 참고하고 있는 파일을 자료구조에 저장하고 
    //일부 LED 정보를 buffer에 복사한다.
    void file_initialize();
    //현재 참조하고 있는 파일의 번호를 올린다.
    void fileup();       
    //현재 참조하고 있는 파일의 번호를 내린다.
    void filedown();

    public:
        Serial_play()
        {
            current_filenum = 0;
            playable = makefilename(current_filenum, current_filename);
            playing = false;

            if(playable)
            {
                printf("File can be opend : %s\n", current_filename);
            }
            else
            {
                printf("File cannot be opend : %s\n", current_filename);
            }
        }

        //Serial에서 들어온 문자열 명령에 따라서 필요한 함수들을 수행한다.
        int play(note* temp);

        //Serial 출력에 필요한 note 배열의 주소를 return하고
        //그 길이를 parameter로 넘겨준다.
        note* getnote(int number, int* length);
        
};