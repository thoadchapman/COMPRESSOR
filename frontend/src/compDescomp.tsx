import { useApp } from './AppContext';

export const useCompDescomp = () => {
  const { URL_BASE, setCompressa, setDecompressa } = useApp();
  return async (comprimir: boolean, textoAlterado: string) => {
    try {
      const endpoint = comprimir ? '/comprimir' : '/decomprimir';
      const response = await fetch(`${URL_BASE}${endpoint}`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          texto: textoAlterado,
          tipo: 'texto'
        })
      });

      const data = await response.json();
      if (comprimir) {
        setCompressa(data.comprimido || data);
      } else {
        setDecompressa(data.descomprimido || data);
      }
    }
    catch (error) {
      console.error("Erro na compressão:", error);
    }
  };
};
