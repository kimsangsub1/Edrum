#include "play.hpp"
#include "serial_protocol.h"

void Serial_play::deallocation()
{
    if(drum1 != NULL)
        delete drum1;
    if(drum2 != NULL)
        delete drum2;
}

void Serial_play::play(note* temp, char* buf)
{
    if(!playing && temp->drum == cmd_playstart)
    {
        // nono
    }
    else if(!playing && temp->drum == cmd_fileup)
    {
        this->fileup(buf);
    }
    else if(!playing && temp->drum == cmd_filedown)
    {
         this->filedown(buf);
    }
    else if(playing && temp->drum == cmd_playend)
    {

    }
}

void Serial_play::file_initialize(char* buf)
{
    char temp[10];
    if(!playable)
    {
        printf("File cannot be opend : %s\n", current_filename);
        return;
    }

    fp.open(current_filename);

    //첫번쨰 드럼
    fp >> temp >> drum1_cnt;
    drum1 = new note[drum1_cnt];
    if(drum1 == NULL)
    {
        fprintf(stderr, "PLAY DRUM1 ALLOCATION ERROR!\n");
        return;
    }
    for(int i=0;i<drum1_cnt;i++)
    {
        fp >> &(drum1[i].power) >> &(drum1[i].msec);
    }

    //두번쨰 드럼
     fp >> temp >> drum2_cnt;
    drum2 = new note[drum2_cnt];
    if(drum2 == NULL)
    {
        fprintf(stderr, "PLAY DRUM2 ALLOCATION ERROR!\n");
        return;
    }
    for(int i=0;i<drum2_cnt;i++)
    {
        fp >> &(drum2[i].power) >> &(drum2[i].msec);
    }
}

void Serial_play::fileup(char* buf)
{
    playable = makefilename(++current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
        sprintf(buf, "OK");
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
        sprintf(buf, "NO");
    }
}

void Serial_play::filedown(char* buf)
{
    if(--current_filenum < 0)
        current_filenum = 0;
    playable = makefilename(--current_filenum, current_filename);
    if(playable)
    {
        printf("File can be opend : %s\n", current_filename);
        sprintf(buf, "OK");
    }
    else
    {
        printf("File cannot be opend : %s\n", current_filename);
        sprintf(buf, "NO");
    }
}