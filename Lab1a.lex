1a) Write a LEX program to recognize valid arithmetic expression. Identifiers in the
expression could be only integers and operators could be + and *. Count the identifiers &amp;
operators present and print them separately.

%{
int id=0, v=0,op=0, flag=0;
%}
%%
[0-9]+ { id++; printf(&quot;%s is an identifier\n&quot;, yytext); }
[+ *] { op++; printf(&quot;%s is an operator\n&quot;, yytext); }
“(“ {v++;}
“)” {if(v&gt;0) v--; else flag=1;}
. { flag=1; }
\n { return; }
%%
main()
{
printf(&quot;Enter an arithmetic expression: &quot;);
yylex();
if ( flag==0 &amp;&amp; id==op+1 &amp;&amp; v==0)
{
printf(&quot;Valid expression\n&quot;);
printf(&quot;The no of identifiers are %d\n&quot;, id);
printf(&quot;The no of operators are %d\n&quot;, op);
}
else
printf(&quot;Invalid expression\n&quot;);
}

Enter an arithmetic expression: 23+78*34
23 is an identifier

+ is an operator
78 is an identifier
* is an operator
34 is an identifier
Valid expression
