#include "bramble.hpp"

#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    const Bramble::GetOpt::Option options[] = {
        {
            .s = "help",
            .c = 'h',
            .value = Bramble::GetOpt::Value::Optional,
            .handler = [](Bramble::GetOpt& self)
            {
                printf("get_opt example\n");
                printf("\n");
                printf("Bramble v%s\n", Bramble::get_version_string());
                printf("\n");
                printf("./main [options]\n");
                printf("\n");
                printf("  --help -h         print this help\n");
                printf("  --required -r     option with required argument\n");
                printf("  --optional -o     option with optional argument\n");
                printf("  --none -n         option with no argument\n");
                printf("\n");
                printf("\n");

                self.stop();
            }
        },
        {
            .s = "required",
            .c = 'r',
            .value = Bramble::GetOpt::Value::Required,
            .handler = [](Bramble::GetOpt& self)
            {
                (void)printf("matched handler for '%.*s': value='%.*s'\n",
                    (int)self.name().size(),
                    self.name().data(),

                    (int)self.value().size(),
                    self.value().data()
                );
            }
        },
        {
            .s = "optional",
            .c = 'o',
            .value = Bramble::GetOpt::Value::Optional,
            .handler = [](Bramble::GetOpt& self)
            {
                (void)printf("matched handler for '%.*s'",
                    (int)self.name().size(),
                    self.name().data()
                );

                if(self.value().empty()){

                    (void)printf("\n");
                }
                else{

                    (void)printf(": value='%.*s'\n",
                        (int)self.value().size(),
                        self.value().data()
                    );
                }
            }
        },
        {
            .s = "none",
            .c = 'n',
            .value = Bramble::GetOpt::Value::None,
            .handler = [](Bramble::GetOpt& self)
            {
                (void)printf("matched handler for '%.*s'\n",
                    (int)self.name().size(),
                    self.name().data()
                );
            }
        }
    };

    // we need to convert an array of null-terminated strings into contiguous memory
    // Bramble::Argument has a constructor for this but we still need to calculate the required
    // working buffer size

    size_t max_working = 0;

    for(auto iter = argv + 1; iter != (argv + argc); ++iter){

        max_working += strlen(*iter);
        max_working += 1;
    }

    std::vector<char> working;

    working.reserve(max_working+1);

    Bramble::Argument arg(argc-1, (const char **)argv+1, working.data(), working.capacity());

    // ok now we can use GetOpt

    Bramble::GetOpt opt(arg.begin(), arg.end(), options, sizeof(options)/sizeof(*options));

    do{

        opt.next();

        if(opt.unknown()){

            printf("error: option '%.*s' is unknown\n", (int)opt.name().size(), opt.name().data());
        }
        else if(opt.missing()){

            printf("error: option '%.*s' requires an argument\n", (int)opt.name().size(), opt.name().data());
        }
        else if(opt.unexpected()){

            printf("error: option '%.*s' must not have an argument\n", (int)opt.name().size(), opt.name().data());
        }
        else{

            // match handler will have been called
        }
    }
    while(!opt.finished());

    return 0;
}
