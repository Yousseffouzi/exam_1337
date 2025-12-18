node *par_num(char **s)
{
    if(accept(s, '('))
    {
        node *n = addition(s);
        if(!accept(s,')'))
        {
            unexpexcted(**s);
            dest
            return(null)
        }
        return (n);
    }
    else if(isdigit(s))
    {
        node n = {VOL, **s - '0', null, null};
        (**s)++;
        return(new_node (n));
    }
    unexp   
    return(null)
}