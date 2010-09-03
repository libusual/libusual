/* gperf header for kwlookup */

%language=ANSI-C
%readonly-tables
%pic
%enum

%define lookup-function-name pg_keyword_lookup_real
%define hash-function-name   pg_keyword_lookup_hash
%define string-pool-name     pgkw

%struct-type
struct PgKeyword { short name; short type; };

%%
