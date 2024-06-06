let R, G, B;
export function SetR(value){
    if (value != null)
        R = value;
    return R;
} 
export function SetG(value){
    if (value != null)
        G = value;
    return G;
} 
export function SetB(value){
    if (value != null)
        B = value;
    return B;
} 
export function getClearColor() {
    return [0, 1, 0, 1];
}