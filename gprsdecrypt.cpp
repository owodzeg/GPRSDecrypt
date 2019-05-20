#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void nop()
{

}

int main(int argc, char* argv[])
{
    uint32_t zero = 0x0;
    uint32_t v0 = 0x1CFD8;
    uint32_t v1 = 0x0;
    uint32_t a0 = 0x9F6B210;
    uint32_t a1 = 0x954A148;
    uint32_t a2 = 0x0;
    uint32_t a3 = 0x954A148;
    uint32_t s0 = 0x1;
    uint32_t s1 = 0x9FFF5F8;
    uint32_t s2 = 0x954A140;
    uint32_t s3 = 0x9F6B210;
    uint32_t s4 = 0x541E0;
    uint32_t s5 = 0x1CFD8;
    uint32_t s6 = 0x8BB7D80;
    uint32_t s7 = 0x8BB7D84;
    uint32_t t0 = 0x0;
    uint32_t t1 = 0x0;
    uint32_t t2 = 0x0;
    uint32_t t3 = 0x0;
    uint32_t t4 = 0x0;
    uint32_t at = 0x0;

    uint32_t GPRS_start = 0x954A140;
    uint32_t GARC_start = 0x9F6B210;
    uint32_t MAGIC_start = 0x8B07558;
    uint32_t MIPS_start = 0x88059B0;

    uint32_t cur_addr = 0x88059B0;

    bool running = true;
    bool jump = false;
    int jump_count = 0;
    uint32_t jump_addr = 0x0;

    string filename = argv[1];
    string garc_filename = filename.substr(filename.find_last_of("\\")+1);
    garc_filename = garc_filename.substr(0,garc_filename.find_first_of(".")) + ".GARC";

    string workdir = argv[0];
    workdir = workdir.substr(0,workdir.find_last_of("\\")+1);

    cout << filename << endl;
    cout << garc_filename << endl;
    cout << workdir << endl;

    string magicdir = workdir+"magic.dat";

    std::ifstream in(filename.c_str(), ios::binary);
    std::vector<char> GPRS_file((std::istreambuf_iterator<char>(in)),
    std::istreambuf_iterator<char>());
    in.close();

    std::vector<uint32_t> MAGIC_file;

    int m_size = filesize(magicdir.c_str()) / 4;

    std::ifstream inn(magicdir.c_str(), ios::binary);

    for(int i=0; i<m_size; i++)
    {
        uint32_t buf;

        inn.seekg(0x4 * i);
        inn.read(reinterpret_cast<char*>(&buf), sizeof(uint32_t));

        MAGIC_file.push_back(buf);
    }

    inn.close();

    std::vector<char> GARC_file;

    while(running)
    {
        ///cout << cur_addr << endl;

        switch(cur_addr)
        {
            case 142629296:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629300:
            {
            a1 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629304:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629308:
            {
            t0 = int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629312:
            {
            t2 = int32_t(-0x100);
            cur_addr += 0x4;
            break;
            }

            case 142629316:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629320:
            {
            if(v0 != zero)
            {
              jump = true;
              jump_addr = 0x088059E4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629324:
            {
            t1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629328:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629332:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629336:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629340:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629344:
            {
            t1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629348:
            {
            if(t1 == zero)
            {
              jump = true;
              jump_addr = 0x088059F8;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629352:
            {
            t3 = v0>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629356:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629360:
            {
            jump = true;
            jump_addr = 0x08805A00;
            cur_addr += 0x4;
            break;
            }

            case 142629364:
            {
            t1 = t0;
            cur_addr += 0x4;
            break;
            }

            case 142629368:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629372:
            {
            t1 = int32_t(0);
            cur_addr += 0x4;
            break;
            }

            case 142629376:
            {
            if(t1 != zero)
            {
              jump = true;
              jump_addr = 0x08805A20;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629380:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629384:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              t1 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              t1 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629388:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629392:
            {
            if(a0 >= 167162384)
            {
              char tmp = t1;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142629396:
            {
            a0 = a0+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629400:
            {
            jump = true;
            jump_addr = 0x08805D14;
            cur_addr += 0x4;
            break;
            }

            case 142629404:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629408:
            {
            if(t3 != zero)
            {
              jump = true;
              jump_addr = 0x08805A3C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629412:
            {
            t1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629416:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629420:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629424:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629428:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629432:
            {
            t1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629436:
            {
            if(t1 == zero)
            {
              jump = true;
              jump_addr = 0x08805A50;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629440:
            {
            v0 = v0>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629444:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629448:
            {
            jump = true;
            jump_addr = 0x08805A58;
            cur_addr += 0x4;
            break;
            }

            case 142629452:
            {
            t1 = t0;
            cur_addr += 0x4;
            break;
            }

            case 142629456:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629460:
            {
            t1 = int32_t(0);
            cur_addr += 0x4;
            break;
            }

            case 142629464:
            {
            if(t1 != t0)
            {
              jump = true;
              jump_addr = 0x08805B54;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629468:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629472:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              t1 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              t1 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629476:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629480:
            {
            t1 = t1|t2;
            cur_addr += 0x4;
            break;
            }

            case 142629484:
            {
            if(v0 != zero)
            {
              jump = true;
              jump_addr = 0x08805A84;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629488:
            {
            t1 = t1<<0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629492:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629496:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629500:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629504:
            {
            v1 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629508:
            {
            t3 = a3&v1;
            cur_addr += 0x4;
            break;
            }

            case 142629512:
            {
            if(t3 == zero)
            {
              jump = true;
              jump_addr = 0x08805A9C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629516:
            {
            v1 = v1>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629520:
            {
            t3 = v1;
            cur_addr += 0x4;
            break;
            }

            case 142629524:
            {
            jump = true;
            jump_addr = 0x08805AA4;
            cur_addr += 0x4;
            break;
            }

            case 142629528:
            {
            t1 = t1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629532:
            {
            t3 = v1;
            cur_addr += 0x4;
            break;
            }

            case 142629536:
            {
            t1 = t1;
            cur_addr += 0x4;
            break;
            }

            case 142629540:
            {
            if(v1 != zero)
            {
              jump = true;
              jump_addr = 0x08805ABC;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629544:
            {
            t1 = t1<<0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629548:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629552:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629556:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629560:
            {
            t3 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629564:
            {
            v0 = a3&t3;
            cur_addr += 0x4;
            break;
            }

            case 142629568:
            {
            if(v0 == zero)
            {
              jump = true;
              jump_addr = 0x08805AD4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629572:
            {
            t3 = t3>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629576:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629580:
            {
            jump = true;
            jump_addr = 0x08805ADC;
            cur_addr += 0x4;
            break;
            }

            case 142629584:
            {
            t1 = t1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629588:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629592:
            {
            t1 = t1;
            cur_addr += 0x4;
            break;
            }

            case 142629596:
            {
            if(t3 != zero)
            {
              jump = true;
              jump_addr = 0x08805AF4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629600:
            {
            t1 = t1<<0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629604:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629608:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629612:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629616:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629620:
            {
            v1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629624:
            {
            if(v1 == zero)
            {
              jump = true;
              jump_addr = 0x08805B0C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629628:
            {
            t3 = v0>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629632:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629636:
            {
            jump = true;
            jump_addr = 0x08805B14;
            cur_addr += 0x4;
            break;
            }

            case 142629640:
            {
            t1 = t1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629644:
            {
            v0 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629648:
            {
            t1 = t1;
            cur_addr += 0x4;
            break;
            }

            case 142629652:
            {
            if(t3 != zero)
            {
              jump = true;
              jump_addr = 0x08805B2C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629656:
            {
            t1 = t1<<0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629660:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629664:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629668:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629672:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629676:
            {
            t3 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629680:
            {
            if(t3 == zero)
            {
              jump = true;
              jump_addr = 0x08805B44;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629684:
            {
            v0 = v0>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629688:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629692:
            {
            jump = true;
            jump_addr = 0x08805B4C;
            cur_addr += 0x4;
            break;
            }

            case 142629696:
            {
            t1 = t1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629700:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629704:
            {
            t1 = t1;
            cur_addr += 0x4;
            break;
            }

            case 142629708:
            {
            jump = true;
            jump_addr = 0x08805B70;
            cur_addr += 0x4;
            break;
            }

            case 142629712:
            {
            t1 = t1+ int32_t(-0xFF);
            cur_addr += 0x4;
            break;
            }

            case 142629716:
            {
            if((a1 >= 156541248) && (a1 < 167162384))
            {
              uint32_t t_addr = 0x0 + a1 - 156541248;
              t1 = GPRS_file[t_addr];
            }
            if(a1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a1 - 167162384;
              t1 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629720:
            {
            if(t1 == zero)
            {
              jump = true;
              jump_addr = 0x08805B68;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629724:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629728:
            {
            jump = true;
            jump_addr = 0x08805B70;
            cur_addr += 0x4;
            break;
            }

            case 142629732:
            {
            t1 = t1|t2;
            cur_addr += 0x4;
            break;
            }

            case 142629736:
            {
            jump = true;
            jump_addr = 0x08805D1C;
            cur_addr += 0x4;
            break;
            }

            case 142629740:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629744:
            {
            t3 = t0;
            cur_addr += 0x4;
            break;
            }

            case 142629748:
            {
            if(v0 != zero)
            {
              jump = true;
              jump_addr = 0x08805B90;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629752:
            {
            v0 = a3&v1;
            cur_addr += 0x4;
            break;
            }

            case 142629756:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629760:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629764:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629768:
            {
            v1 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629772:
            {
            v0 = a3&v1;
            cur_addr += 0x4;
            break;
            }

            case 142629776:
            {
            if(v0 == zero)
            {
              jump = true;
              jump_addr = 0x08805BA4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629780:
            {
            v1 = v1>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629784:
            {
            v0 = v1;
            cur_addr += 0x4;
            break;
            }

            case 142629788:
            {
            jump = true;
            jump_addr = 0x08805BAC;
            cur_addr += 0x4;
            break;
            }

            case 142629792:
            {
            t4 = t0;
            cur_addr += 0x4;
            break;
            }

            case 142629796:
            {
            v0 = v1;
            cur_addr += 0x4;
            break;
            }

            case 142629800:
            {
            t4 = int32_t(0);
            cur_addr += 0x4;
            break;
            }

            case 142629804:
            {
            if(t4 != t0)
            {
              jump = true;
              jump_addr = 0x08805BF4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629808:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629812:
            {
            if(v1 != zero)
            {
              jump = true;
              jump_addr = 0x08805BCC;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629816:
            {
            t3 = t3<<0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629820:
            {
            if((a2 >= 156541248) && (a2 < 167162384))
            {
              uint32_t t_addr = 0x0 + a2 - 156541248;
              a3 = GPRS_file[t_addr];
            }
            if(a2 >= 167162384)
            {
              uint32_t t_addr = 0x0 + a2 - 167162384;
              a3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629824:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629828:
            {
            a1 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142629832:
            {
            v0 = int32_t(0x80);
            cur_addr += 0x4;
            break;
            }

            case 142629836:
            {
            v1 = a3&v0;
            cur_addr += 0x4;
            break;
            }

            case 142629840:
            {
            if(v1 == zero)
            {
              jump = true;
              jump_addr = 0x08805BE4;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629844:
            {
            v0 = v0>>0x1;
            cur_addr += 0x4;
            break;
            }

            case 142629848:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629852:
            {
            jump = true;
            jump_addr = 0x08805BEC;
            cur_addr += 0x4;
            break;
            }

            case 142629856:
            {
            t3 = t3+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629860:
            {
            v1 = v0;
            cur_addr += 0x4;
            break;
            }

            case 142629864:
            {
            t3 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142629868:
            {
            jump = true;
            jump_addr = 0x08805B74;
            cur_addr += 0x4;
            break;
            }

            case 142629872:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629876:
            {
            if(t3 < 0x7)
            {
              a2 = 1;
            }
            else
            {
              a2 = 0;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629880:
            {
            if(a2 == zero)
            {
              jump = true;
              jump_addr = 0x08805C28;
              cur_addr += 0x4;
            }
            else
            {
              cur_addr += 0x8;
            }
            break;
            }

            case 142629884:
            {
            t3 = t3+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629888:
            {
            if(t3 < 0)
            {
              jump = true;
              jump_addr = 0x08805D14;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629892:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629896:
            {
            v1 = a0+t1;
            cur_addr += 0x4;
            break;
            }

            case 142629900:
            {
            if((v1 >= 156541248) && (v1 < 167162384))
            {
              uint32_t t_addr = 0x0 + v1 - 156541248;
              v1 = GPRS_file[t_addr];
            }
            if(v1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + v1 - 167162384;
              v1 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629904:
            {
            t3 = t3+ int32_t(-0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629908:
            {
            if(a0 >= 167162384)
            {
              char tmp = v1;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142629912:
            {
            if((int32_t)t3 >= 0)
            {
              jump = true;
              jump_addr = 0x08805C08;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629916:
            {
            a0 = a0+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142629920:
            {
            jump = true;
            jump_addr = 0x08805D14;
            cur_addr += 0x4;
            break;
            }

            case 142629924:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629928:
            {
            a2 = t3>>0x3;
            cur_addr += 0x4;
            break;
            }

            case 142629932:
            {
            t3 = t3&0x7;
            cur_addr += 0x4;
            break;
            }

            case 142629936:
            {
            v1 = t3+ int32_t(-0x8);
            cur_addr += 0x4;
            break;
            }

            case 142629940:
            {
            a0 = a0+v1;
            cur_addr += 0x4;
            break;
            }

            case 142629944:
            {
            if(t3 < 0x8)
            {
              v1 = 1;
            }
            else
            {
              v1 = 0;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629948:
            {
            if(v1 == zero)
            {
              jump = true;
              jump_addr = 0x08805C5C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142629952:
            {
            t1 = a0+t1;
            cur_addr += 0x4;
            break;
            }

            case 142629956:
            {
            t3 = t3<<0x2;
            cur_addr += 0x4;
            break;
            }

            case 142629960:
            {
            at = 0x8B00000;
            cur_addr += 0x4;
            break;
            }

            case 142629964:
            {
            at = at+t3;
            cur_addr += 0x4;
            break;
            }

            case 142629968:
            {
            uint32_t tmp;
            uint32_t t_addr = 0x7558 + at - 145782104;
            at = (int32_t)MAGIC_file[(t_addr/4)];

            cur_addr += 0x4;
            break;
            }

            case 142629972:
            {
            jump = true;
            jump_addr = at;
            cur_addr += 0x4;
            break;
            }

            case 142629976:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142629980:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x0 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x0 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629984:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142629988:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x1 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x1 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142629992:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142629996:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x2 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x2 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630000:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630004:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x3 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x3 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630008:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630012:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x4 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x4 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630016:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630020:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x5 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x5 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630024:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630028:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x6 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x6 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630032:
            {
            if(a0 >= 167162384)
            {
              char tmp = t3;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630036:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x7 + t1 - 156541248;
              v1 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x7 + t1 - 167162384;
              v1 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630040:
            {
            t3 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142630044:
            {
            a2 = a0+ int32_t(0x8);
            cur_addr += 0x4;
            break;
            }

            case 142630048:
            {
            if(a0 >= 167162384)
            {
              char tmp = v1;
              GARC_file.push_back(tmp);
            }
            cur_addr += 0x4;
            break;
            }

            case 142630052:
            {
            t1 = t1+ int32_t(0x8);
            cur_addr += 0x4;
            break;
            }

            case 142630056:
            {
            a0 = t3+ int32_t(-0x1);
            cur_addr += 0x4;
            break;
            }

            case 142630060:
            {
            t3 = a0;
            cur_addr += 0x4;
            break;
            }

            case 142630064:
            {
            a0 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142630068:
            {
            a2 = t3;
            cur_addr += 0x4;
            break;
            }

            case 142630072:
            {
            if((int32_t)a2 >= 0)
            {
              jump = true;
              jump_addr = 0x08805C5C;
            }
            cur_addr += 0x4;
            break;
            }

            case 142630076:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142630080:
            {
            jump = true;
            jump_addr = 0x08805D14;
            cur_addr += 0x4;
            break;
            }

            case 142630084:
            {
            a2 = a1+ int32_t(0x1);
            cur_addr += 0x4;
            break;
            }

            case 142630088:
            {
            jump = true;
            jump_addr = 0x08805C68;
            cur_addr += 0x4;
            break;
            }

            case 142630092:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x1 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x1 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630096:
            {
            jump = true;
            jump_addr = 0x08805C70;
            cur_addr += 0x4;
            break;
            }

            case 142630100:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x2 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x2 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630104:
            {
            jump = true;
            jump_addr = 0x08805C78;
            cur_addr += 0x4;
            break;
            }

            case 142630108:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x3 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x3 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630112:
            {
            jump = true;
            jump_addr = 0x08805C80;
            cur_addr += 0x4;
            break;
            }

            case 142630116:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x4 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x4 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630120:
            {
            jump = true;
            jump_addr = 0x08805C88;
            cur_addr += 0x4;
            break;
            }

            case 142630124:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x5 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x5 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630128:
            {
            jump = true;
            jump_addr = 0x08805C90;
            cur_addr += 0x4;
            break;
            }

            case 142630132:
            {
            if((t1 >= 156541248) && (t1 < 167162384))
            {
              uint32_t t_addr = 0x6 + t1 - 156541248;
              t3 = GPRS_file[t_addr];
            }
            if(t1 >= 167162384)
            {
              uint32_t t_addr = 0x6 + t1 - 167162384;
              t3 = (int32_t)GARC_file[t_addr];
            }
            cur_addr += 0x4;
            break;
            }

            case 142630136:
            {
            jump = true;
            jump_addr = 0x08805C94;
            cur_addr += 0x4;
            break;
            }

            case 142630140:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142630144:
            {
            t3 = a2;
            cur_addr += 0x4;
            break;
            }

            case 142630148:
            {
            a2 = a0+ int32_t(0x8);
            cur_addr += 0x4;
            break;
            }

            case 142630152:
            {
            t1 = t1+ int32_t(0x8);
            cur_addr += 0x4;
            break;
            }

            case 142630156:
            {
            jump = true;
            jump_addr = 0x08805CAC;
            cur_addr += 0x4;
            break;
            }

            case 142630160:
            {
            a0 = t3+ int32_t(-0x1);
            cur_addr += 0x4;
            break;
            }

            case 142630164:
            {
            jump = true;
            jump_addr = 0x088059C8;
            cur_addr += 0x4;
            break;
            }

            case 142630168:
            {
            nop();
            cur_addr += 0x4;
            break;
            }

            case 142630172:
            {
            cur_addr += 0x4;
            break;
            }

            case 142630176:
            {
            nop();
            running = false;
            cur_addr += 0x4;
            break;
            }
        }

        if(jump_count >= 1)
        {
            jump_count = 0;
            cur_addr = jump_addr;
        }

        if(jump)
        {
            jump = false;
            jump_count = 1;
        }
    }

    ofstream garc_out(garc_filename.c_str(),ios::binary);

    for(int i=0; i<GARC_file.size(); i++)
    {
        garc_out.put(GARC_file[i]);
    }

    garc_out.close();

    return 0;
}
