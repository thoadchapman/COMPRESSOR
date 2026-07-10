export type Operacao = {
    endpoint: string;
    extrairDados: (data: any) => string;
    setEstado: (valor: string) => void;
    tipo: string
};

export type Modo = {
    COMPRIMIR: Operacao;
    DESCOMPRIMIR: Operacao;
};
