import { useApp } from './AppContext';

type Operacao = {
  endpoint: string;
  extrairDados: (data: any) => string;
  setEstado: (valor: string) => void;
  tipo: string
};

type Modo = {
  COMPRIMIR: Operacao;
  DESCOMPRIMIR: Operacao;
};

export const OPCOES = (): Modo => {
  const { setComprimida, setDescomprimida } = useApp();
  return {
    COMPRIMIR: {
      endpoint: '/comprimir',
      extrairDados: (data: { comprimido?: string }) => data.comprimido || '',
      setEstado: setComprimida,
      tipo: 'texto'
    },
    DESCOMPRIMIR: {
      endpoint: '/descomprimir',
      extrairDados: (data: { comprimido?: string }) => data.comprimido || '',
      setEstado: setDescomprimida,
      tipo: 'texto'
    }
  }
}

export const useComp = () => {
  const { URL_BASE } = useApp();
  const opcoes = OPCOES();
  return async (opcaoSolicitada: keyof Modo, dados: string | File) => {
    try {
      const opcao: Operacao = opcoes[opcaoSolicitada];
      const response = await fetch(`${URL_BASE}${opcao.endpoint}`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          dados: dados,
          tipo: opcao.tipo
        })
      });

      const data = await response.json();
      opcao.setEstado(data);
    }
    catch (error) {
      console.error("Erro na compressão:", error);
    }
  };
};
