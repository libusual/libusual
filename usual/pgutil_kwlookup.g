/* gperf header for kwlookup */

%language=ANSI-C
%readonly-tables
%pic

%define lookup-function-name pg_keyword_lookup_hash

%struct-type
struct PgKeyword { short name; short type; };

%%
