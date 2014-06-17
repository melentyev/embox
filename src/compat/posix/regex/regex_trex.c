/**
 * @file
 *
 * @date Jun 13, 2014
 * @author Anton Bondarev
 */


#include <regex.h>
#include <trex.h>
#include <string.h>
#include <errno.h>

int regcomp(regex_t *preg, const char *regex, int cflags) {
	preg->regex_extended = trex_compile((char *)regex, (const char**) &preg->regex_error);
	return 0;
}

int regexec(const regex_t *preg, const char *string, size_t nmatch,
        regmatch_t pmatch[], int eflags) {
	const char _begin, _end;
	const char *begin = &_begin, *end = &_end;
	const char *str_beg = string, *str_end = string + strlen(string);
	int count = 0;

	if (!pmatch) {
		return -EINVAL;
	}

	if (!preg->regex_extended) {
		return -EINVAL;
	}

	while (trex_searchrange(preg->regex_extended, str_beg, str_end,
			&begin, &end)) {
		if (nmatch <= count) {
			break;
		}

		pmatch[count].rm_so = begin - string;
		pmatch[count].rm_eo = end - string;

		str_beg = begin + 1;
		count++;
	}

	return 0;
}

size_t regerror(int errcode, const regex_t *preg, char *errbuf,
        size_t errbuf_size) {
	return 0;
}

void regfree(regex_t *preg) {

}
