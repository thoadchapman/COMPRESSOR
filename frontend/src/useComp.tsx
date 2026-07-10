import { useApp } from './AppContext';
import { Modo, Operacao } from './Modo'

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

const fileToString = (arquivo: File | string): Promise<string> => {
  if (typeof arquivo === "string") {
    return Promise.resolve(arquivo);
  }
  return new Promise((resolve) => {
    const reader = new FileReader();
    reader.onload = () => {
      const base64 = btoa(String.fromCharCode(...new Uint8Array(reader.result as ArrayBuffer)));
      resolve(base64);
    };
    reader.readAsArrayBuffer(arquivo);
  });
};

export const useComp = () => {
  const { URL_BASE, setOriginal, setOriginalString } = useApp();
  const opcoes = OPCOES();
  return async (opcaoSolicitada: keyof Modo, dados: string | File) => {
    try {
      setOriginal(dados);
      let dadosString = dados;
      if (dadosString instanceof File) { dadosString = await fileToString(dados); }
      setOriginalString(dadosString);
      const opcao: Operacao = opcoes[opcaoSolicitada];
      const response = await fetch(`${URL_BASE}${opcao.endpoint}`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          dados: dadosString,
          tipo: opcao.tipo
        })
      });

      const data = await response.json();
      opcao.setEstado(data.comprimido);
    }
    catch (error) {
      console.error("Erro na compressão:", error);
    }
  };
};
