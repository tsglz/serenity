/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <AK/String.h>
#include <LibCore/DateTime.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv)
{
    if (pledge("stdio settime", nullptr) < 0) {
        perror("pledge");
        return 1;
    }

    time_t now = time(nullptr);

    if (argc == 2 && !strcmp(argv[1], "-u")) {
        printf("%lld\n", now);
        return 0;
    }
    if (argc == 3 && !strcmp(argv[1], "-s")) {
        bool ok;
        timespec ts = { String(argv[2]).to_uint(ok), 0 };
        if (!ok) {
            fprintf(stderr, "date: Invalid timestamp value");
            return 1;
        }
        if (clock_settime(CLOCK_REALTIME, &ts) < 0) {
            perror("clock_settime");
            return 1;
        }
        return 0;
    }

    printf("%s\n", Core::DateTime::from_timestamp(now).to_string().characters());
    return 0;
}
