import { createContext, useContext, useState, ReactNode } from 'react';

type ContextType = {
  PORTA: string;
  SERVIDOR_ID: string;
  URL_BASE: string;
  comprimida: string;
  setComprimida: (data: string) => void;
  descomprimida: string;
  setDescomprimida: (data: string) => void;
  original: string | File | null;
  setOriginal: (data: string | File | null) => void;
  originalString: string;
  setOriginalString: (data: string) => void;
}

const AppContext = createContext<ContextType | undefined>(undefined);

type AppProviderProps = {
  children: ReactNode;
}

export const AppProvider = ({ children }: AppProviderProps) => {
  const PORTA = "8080";
  const SERVIDOR_ID = "localhost:" + PORTA;
  const URL_BASE = `http://${SERVIDOR_ID}`;

  const [descomprimida, setDescomprimida] = useState<string>("");
  const [comprimida, setComprimida] = useState<string>("");
  const [originalString, setOriginalString] = useState<string>("");
  const [original, setOriginal] = useState<string | File | null>("");

  return (
    <AppContext.Provider value={{
      PORTA,
      SERVIDOR_ID,
      URL_BASE,
      descomprimida,
      setDescomprimida,
      comprimida,
      setComprimida,
      original,
      setOriginal,
      originalString,
      setOriginalString
    }}>
      {children}
    </AppContext.Provider>
  );
};

export const useApp = (): ContextType => {
  const context = useContext(AppContext);
  if (context === undefined) {
    throw new Error('useApp deve ser utilizado dentro de um AppProvider');
  }
  return context;
};