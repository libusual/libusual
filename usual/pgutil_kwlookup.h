/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -m5 usual/pgutil_kwlookup.gp  */
/* Computed positions: -k'1-2,6,9,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

/* maximum key range = 324, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
pg_keyword_lookup_hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329,  22,  32,  55,
       85,   5,  84, 101,  84,  26,   2,   9,  16, 114,
        9,   1,  71, 329,   3,  32,   1,  58, 105,  37,
        2, 131,   4, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329, 329, 329, 329, 329,
      329, 329, 329, 329, 329, 329
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const char *
pg_keyword_lookup_real (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 146,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 17,
      MIN_HASH_VALUE = 5,
      MAX_HASH_VALUE = 328
    };

  struct pgkw_t
    {
      char pgkw_str5[sizeof("to")];
      char pgkw_str9[sizeof("or")];
      char pgkw_str10[sizeof("treat")];
      char pgkw_str12[sizeof("order")];
      char pgkw_str13[sizeof("true")];
      char pgkw_str14[sizeof("not")];
      char pgkw_str15[sizeof("except")];
      char pgkw_str16[sizeof("join")];
      char pgkw_str19[sizeof("none")];
      char pgkw_str21[sizeof("on")];
      char pgkw_str26[sizeof("left")];
      char pgkw_str27[sizeof("least")];
      char pgkw_str28[sizeof("real")];
      char pgkw_str30[sizeof("else")];
      char pgkw_str33[sizeof("table")];
      char pgkw_str35[sizeof("right")];
      char pgkw_str36[sizeof("time")];
      char pgkw_str37[sizeof("localtime")];
      char pgkw_str39[sizeof("int")];
      char pgkw_str40[sizeof("into")];
      char pgkw_str41[sizeof("inout")];
      char pgkw_str42[sizeof("some")];
      char pgkw_str43[sizeof("inner")];
      char pgkw_str44[sizeof("row")];
      char pgkw_str45[sizeof("select")];
      char pgkw_str46[sizeof("in")];
      char pgkw_str47[sizeof("analyze")];
      char pgkw_str48[sizeof("limit")];
      char pgkw_str49[sizeof("notnull")];
      char pgkw_str50[sizeof("integer")];
      char pgkw_str51[sizeof("like")];
      char pgkw_str52[sizeof("ilike")];
      char pgkw_str54[sizeof("new")];
      char pgkw_str57[sizeof("all")];
      char pgkw_str58[sizeof("between")];
      char pgkw_str60[sizeof("references")];
      char pgkw_str62[sizeof("bit")];
      char pgkw_str63[sizeof("out")];
      char pgkw_str64[sizeof("national")];
      char pgkw_str66[sizeof("bigint")];
      char pgkw_str67[sizeof("outer")];
      char pgkw_str69[sizeof("collate")];
      char pgkw_str70[sizeof("extract")];
      char pgkw_str71[sizeof("boolean")];
      char pgkw_str72[sizeof("nchar")];
      char pgkw_str74[sizeof("create")];
      char pgkw_str75[sizeof("analyse")];
      char pgkw_str76[sizeof("natural")];
      char pgkw_str77[sizeof("exists")];
      char pgkw_str78[sizeof("intersect")];
      char pgkw_str79[sizeof("constraint")];
      char pgkw_str80[sizeof("column")];
      char pgkw_str81[sizeof("union")];
      char pgkw_str82[sizeof("cast")];
      char pgkw_str83[sizeof("unique")];
      char pgkw_str86[sizeof("case")];
      char pgkw_str87[sizeof("null")];
      char pgkw_str88[sizeof("as")];
      char pgkw_str89[sizeof("do")];
      char pgkw_str90[sizeof("similar")];
      char pgkw_str91[sizeof("for")];
      char pgkw_str92[sizeof("is")];
      char pgkw_str93[sizeof("offset")];
      char pgkw_str95[sizeof("cross")];
      char pgkw_str96[sizeof("isnull")];
      char pgkw_str97[sizeof("user")];
      char pgkw_str98[sizeof("then")];
      char pgkw_str101[sizeof("coalesce")];
      char pgkw_str102[sizeof("end")];
      char pgkw_str103[sizeof("freeze")];
      char pgkw_str105[sizeof("old")];
      char pgkw_str106[sizeof("float")];
      char pgkw_str108[sizeof("localtimestamp")];
      char pgkw_str110[sizeof("grant")];
      char pgkw_str111[sizeof("session_user")];
      char pgkw_str112[sizeof("asc")];
      char pgkw_str113[sizeof("over")];
      char pgkw_str114[sizeof("default")];
      char pgkw_str115[sizeof("position")];
      char pgkw_str116[sizeof("false")];
      char pgkw_str118[sizeof("greatest")];
      char pgkw_str119[sizeof("and")];
      char pgkw_str121[sizeof("both")];
      char pgkw_str122[sizeof("trim")];
      char pgkw_str124[sizeof("deferrable")];
      char pgkw_str125[sizeof("xmlroot")];
      char pgkw_str126[sizeof("setof")];
      char pgkw_str127[sizeof("authorization")];
      char pgkw_str129[sizeof("distinct")];
      char pgkw_str130[sizeof("xmlforest")];
      char pgkw_str131[sizeof("where")];
      char pgkw_str132[sizeof("xmlparse")];
      char pgkw_str133[sizeof("precision")];
      char pgkw_str134[sizeof("when")];
      char pgkw_str135[sizeof("decimal")];
      char pgkw_str136[sizeof("xmlconcat")];
      char pgkw_str138[sizeof("leading")];
      char pgkw_str139[sizeof("trailing")];
      char pgkw_str140[sizeof("current_time")];
      char pgkw_str141[sizeof("xmlelement")];
      char pgkw_str142[sizeof("current_role")];
      char pgkw_str143[sizeof("window")];
      char pgkw_str145[sizeof("only")];
      char pgkw_str146[sizeof("char")];
      char pgkw_str147[sizeof("xmlpi")];
      char pgkw_str148[sizeof("dec")];
      char pgkw_str149[sizeof("desc")];
      char pgkw_str150[sizeof("asymmetric")];
      char pgkw_str151[sizeof("with")];
      char pgkw_str152[sizeof("xmlserialize")];
      char pgkw_str153[sizeof("check")];
      char pgkw_str154[sizeof("verbose")];
      char pgkw_str155[sizeof("numeric")];
      char pgkw_str159[sizeof("varchar")];
      char pgkw_str161[sizeof("array")];
      char pgkw_str162[sizeof("full")];
      char pgkw_str164[sizeof("interval")];
      char pgkw_str165[sizeof("any")];
      char pgkw_str168[sizeof("overlaps")];
      char pgkw_str172[sizeof("off")];
      char pgkw_str178[sizeof("fetch")];
      char pgkw_str179[sizeof("timestamp")];
      char pgkw_str180[sizeof("group")];
      char pgkw_str181[sizeof("smallint")];
      char pgkw_str190[sizeof("current_schema")];
      char pgkw_str194[sizeof("xmlattributes")];
      char pgkw_str195[sizeof("current_user")];
      char pgkw_str196[sizeof("using")];
      char pgkw_str197[sizeof("values")];
      char pgkw_str202[sizeof("foreign")];
      char pgkw_str204[sizeof("placing")];
      char pgkw_str205[sizeof("from")];
      char pgkw_str209[sizeof("character")];
      char pgkw_str211[sizeof("current_timestamp")];
      char pgkw_str215[sizeof("primary")];
      char pgkw_str224[sizeof("current_date")];
      char pgkw_str228[sizeof("returning")];
      char pgkw_str241[sizeof("nullif")];
      char pgkw_str266[sizeof("overlay")];
      char pgkw_str275[sizeof("variadic")];
      char pgkw_str283[sizeof("symmetric")];
      char pgkw_str293[sizeof("current_catalog")];
      char pgkw_str304[sizeof("substring")];
      char pgkw_str314[sizeof("having")];
      char pgkw_str326[sizeof("binary")];
      char pgkw_str328[sizeof("initially")];
    };
  static const struct pgkw_t pgkw_contents =
    {
      "to",
      "or",
      "treat",
      "order",
      "true",
      "not",
      "except",
      "join",
      "none",
      "on",
      "left",
      "least",
      "real",
      "else",
      "table",
      "right",
      "time",
      "localtime",
      "int",
      "into",
      "inout",
      "some",
      "inner",
      "row",
      "select",
      "in",
      "analyze",
      "limit",
      "notnull",
      "integer",
      "like",
      "ilike",
      "new",
      "all",
      "between",
      "references",
      "bit",
      "out",
      "national",
      "bigint",
      "outer",
      "collate",
      "extract",
      "boolean",
      "nchar",
      "create",
      "analyse",
      "natural",
      "exists",
      "intersect",
      "constraint",
      "column",
      "union",
      "cast",
      "unique",
      "case",
      "null",
      "as",
      "do",
      "similar",
      "for",
      "is",
      "offset",
      "cross",
      "isnull",
      "user",
      "then",
      "coalesce",
      "end",
      "freeze",
      "old",
      "float",
      "localtimestamp",
      "grant",
      "session_user",
      "asc",
      "over",
      "default",
      "position",
      "false",
      "greatest",
      "and",
      "both",
      "trim",
      "deferrable",
      "xmlroot",
      "setof",
      "authorization",
      "distinct",
      "xmlforest",
      "where",
      "xmlparse",
      "precision",
      "when",
      "decimal",
      "xmlconcat",
      "leading",
      "trailing",
      "current_time",
      "xmlelement",
      "current_role",
      "window",
      "only",
      "char",
      "xmlpi",
      "dec",
      "desc",
      "asymmetric",
      "with",
      "xmlserialize",
      "check",
      "verbose",
      "numeric",
      "varchar",
      "array",
      "full",
      "interval",
      "any",
      "overlaps",
      "off",
      "fetch",
      "timestamp",
      "group",
      "smallint",
      "current_schema",
      "xmlattributes",
      "current_user",
      "using",
      "values",
      "foreign",
      "placing",
      "from",
      "character",
      "current_timestamp",
      "primary",
      "current_date",
      "returning",
      "nullif",
      "overlay",
      "variadic",
      "symmetric",
      "current_catalog",
      "substring",
      "having",
      "binary",
      "initially"
    };
  #define pgkw ((const char *) &pgkw_contents)
  static const int wordlist[] =
    {
      -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str5,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str9,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str10,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str12,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str13,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str14,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str15,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str16,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str19,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str21,
      -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str26,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str27,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str28,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str30,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str33,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str35,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str36,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str37,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str39,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str40,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str41,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str42,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str43,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str44,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str45,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str46,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str47,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str48,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str49,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str50,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str51,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str52,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str54,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str57,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str58,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str60,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str62,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str63,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str64,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str66,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str67,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str69,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str70,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str71,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str72,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str74,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str75,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str76,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str77,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str78,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str79,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str80,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str81,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str82,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str83,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str86,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str87,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str88,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str89,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str90,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str91,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str92,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str93,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str95,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str96,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str97,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str98,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str101,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str102,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str103,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str105,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str106,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str108,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str110,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str111,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str112,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str113,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str114,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str115,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str116,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str118,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str119,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str121,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str122,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str124,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str125,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str126,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str127,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str129,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str130,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str131,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str132,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str133,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str134,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str135,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str136,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str138,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str139,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str140,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str141,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str142,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str143,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str145,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str146,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str147,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str148,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str149,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str150,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str151,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str152,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str153,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str154,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str155,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str159,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str161,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str162,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str164,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str165,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str168,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str172,
      -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str178,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str179,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str180,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str181,
      -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str190,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str194,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str195,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str196,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str197,
      -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str202,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str204,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str205,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str209,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str211,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str215,
      -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str224,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str228,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str241,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str266,
      -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str275,
      -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str283,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str293,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str304,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str314,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str326,
      -1,
      (int)(long)&((struct pgkw_t *)0)->pgkw_str328
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = pg_keyword_lookup_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = wordlist[key];
          if (o >= 0)
            {
              register const char *s = o + pgkw;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return s;
            }
        }
    }
  return 0;
}
