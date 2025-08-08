char* pangrams(char* s) {
    static char* yes = "pangram";
    static char* no = "not pangram";
    bool found[26] = {false};
    int i;  

    
    for (i = 0; s[i] != '\0'; i++) {
        char character = tolower(s[i]); 
        if (character >= 'a' && character <= 'z') {
            found[character - 'a'] = true;  
        }
    }

    
    for (i = 0; i < 26; i++) {
        if (!found[i]) {
            return no;
        }
    }

    return yes;
}